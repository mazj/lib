#ifndef THREAD_MGR_H
#define THREAD_MGR_H

#include <QThread>
#include <QQueue>
#include <QList>
#include <QHash>

#include "singletonutils.h"


#define g_threadMgr ThreadMgr::instance()


/*!
 * \brief The ThreadMgr class
 * 程管理类，类似于一个线程池，单例类
 * 两种初始化方式，一种是每个线程处理的连接数，一个是一共多少个线程
 */
class ThreadMgr
{
    DECLARE_SINGLETON(ThreadMgr)

public:
    enum ThreadType
    {
        THREADSIZE, // 固定线程数
        HANDLESIZE, // 固定每个线程处理多少连接
    };

public:
    ~ThreadMgr();

public:
    /*!
     * \brief getThread 获得一个线程
     * \return
     */
    QThread *getThread();

    /*!
     * \brief initThreadType 初始化线程管理的方式
     * \param type
     * \param max
     */
    void initThreadType(ThreadType type = HANDLESIZE, unsigned int max = 1000);

    /*!
     * \brief removeThread 连接断开，线程计数减一
     */
    void removeThread(QThread *);

    /*!
     * \brief clear 清空计数
     */
    void clear();

private:
    ThreadMgr();

    /*!
     * \brief initThreadSize 新建固定线程和启动
     */
    void initThreadSize();

    /*!
     * \brief findThreadSize 固定线程数的查找
     * \return
     */
    QThread *findThreadSize();

    /*!
     * \brief findHandleSize 固定连接数查找
     * \return
     */
    QThread *findHandleSize();

private:
    ThreadType m_type; // 线程类型
    unsigned int m_size; // 最大值
    QHash<QThread *, unsigned int> m_threadSizeMap; // 保存每个线程的数目
    bool m_initfist; // 是否是第一次初始化，只允许初始化一次。
};

#endif // THREAD_MGR_H
