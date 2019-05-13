#include "threadmgr.h"

ThreadMgr::ThreadMgr()
{
    m_initfist = false;
}

ThreadMgr::~ThreadMgr() //停止所有线程，并释放资源
{
    QThread *tmp;
    for (auto it = m_threadSizeMap.begin(); it != m_threadSizeMap.end(); ++it)
    {
        tmp = it.key();
        tmp->quit();
        tmp->wait(1000);
        if (!tmp->isFinished())
        {
            tmp->terminate();
        }

        delete tmp;
    }
}

QThread *ThreadMgr::getThread()
{
    if (!m_initfist)
    {
        initThreadType(THREADSIZE, 10);
    }

    if (m_type == THREADSIZE)
    {
        return findThreadSize();
    }

    return findHandleSize();
}

void ThreadMgr::removeThread(QThread *thread)
{
    auto t = m_threadSizeMap.find(thread);
    if (t != m_threadSizeMap.end())
    {
        t.value() --;
        if (m_type == HANDLESIZE && t.value() == 0 && m_threadSizeMap.size() > 1)
        {
            m_threadSizeMap.remove(thread);
            thread->exit();
            thread->wait(3000);

            delete thread;
        }
    }
}

void ThreadMgr::initThreadType(ThreadType type, unsigned int max)
{
    // 只用初始化一次
    if (m_initfist)
    {
        return;
    }
    m_initfist = true;

    m_type = type;
    m_size = max;

    // size不指定时
    if (m_size == 0)
    {
        if(type == THREADSIZE) // 当选用固定线程方案时，默认固定为10个线程，每个线程可供多个对象使用
        {
            m_size = 10;
        }
        else // 当选固定连接个数时，默认固定一个线程供1000个对象使用，超过次数时，创建新线程
        {
            m_size = 1000;
        }
    }

    if (type == THREADSIZE)
    {
        initThreadSize();
    }
    else
    {
        QThread *tmp = new QThread;
        m_threadSizeMap.insert(tmp, 0);
        tmp->start();
    }

}

void ThreadMgr::initThreadSize() //建立好线程并启动，
{
    QThread *tmp;

    for (unsigned int i = 0; i < m_size; ++i)
    {
        tmp = new QThread;
        m_threadSizeMap.insert(tmp, 0);
        tmp->start();
    }
}

QThread *ThreadMgr::findHandleSize() //查找到线程里的连接数小于最大值就返回查找到的，找不到就新建一个线程
{
    for (auto it  = m_threadSizeMap.begin(); it != m_threadSizeMap.end(); ++it)
    {
        if (it.value() < m_size)
        {
            it.value() ++;
            return it.key();
        }
    }

    QThread *tmp = new QThread;
    m_threadSizeMap.insert(tmp, 1);
    tmp->start();

    return tmp;
}

QThread *ThreadMgr::findThreadSize() //遍历查找所有线程中连接数最小的那个，返回
{
    auto it = m_threadSizeMap.begin();
    auto ite = m_threadSizeMap.begin();
    for (++it ; it != m_threadSizeMap.end(); ++it)
    {
        if (it.value() < ite.value())
        {
            ite = it;
        }
    }
    ite.value() ++;

    return ite.key();
}

void ThreadMgr::clear()//仅仅清空计数，线程不释放
{
    for (auto it = m_threadSizeMap.begin(); it != m_threadSizeMap.end(); ++it)
    {
        it.value() = 0;
    }
}
