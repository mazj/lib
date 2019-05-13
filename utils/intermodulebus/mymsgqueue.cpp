#include <QMutexLocker>

#include "mymsgqueue.h"
#include "absmsgobj.h"

static const int TIME_INTERVAL = 5; // 50ms

MyMsgQueue::MyMsgQueue(QObject *parent)
    : QObject(parent)
{
    m_msgInfos.clear();
    m_msgObjs.clear();

    startTimer(TIME_INTERVAL);
}

void MyMsgQueue::msgObjRegister(const QString &key, AbsMsgObj *msgObj)
{
    m_msgObjs[key] << msgObj;
}

void MyMsgQueue::msgObjUnregister(const QString &key, AbsMsgObj *msgObj)
{
    if (m_msgObjs.contains(key))
    {
        m_msgObjs[key].remove(msgObj);

        if (m_msgObjs[key].isEmpty())
        {
            m_msgObjs.remove(key);
        }
    }
}

bool MyMsgQueue::sendMsg(const InterModuleBus::Msg &msg)
{
    auto it = m_msgObjs.find(msg.dst);
    if (it == m_msgObjs.end())
    {
        return false;
    }

    for (AbsMsgObj *msgObj : it.value())
    {
        msgObj->getMsg(msg);
    }

    return true;
}

bool MyMsgQueue::sendMsg(const QString &dst, int type, const QVariant &msgData, bool isAsync)
{
    InterModuleBus::Msg msg;
    msg.dst = dst;
    msg.type = type;
    msg.data = msgData;

    // 异步
    if (isAsync)
    {
        QMutexLocker locker(&m_mutex);
        m_msgInfos.enqueue(msg);
        return true;
    }

    // 同步
    return sendMsg(msg);
}

bool MyMsgQueue::sendMsg(const QStringList &dstList, int type, const QVariant &msgData, bool isAsync)
{
    bool result = true;

    for (const QString &dst : dstList)
    {
        // 认为只要有一个出错就错了
        result &= sendMsg(dst, type, msgData, isAsync);
    }

    return result;
}

void MyMsgQueue::broadcastMsg(const int type, const QVariant &msgData, const QString &srcModuleName)
{
    for (auto it2 = m_msgObjs.begin(); it2 != m_msgObjs.end(); it2++)
    {
        for (const AbsMsgObj* obj : it2.value())
        {
            InterModuleBus::Msg msg;
            QString moduleName = obj->getModuleName();
            if (srcModuleName == moduleName)
                continue;
            msg.dst = moduleName;
            msg.type = type;
            msg.data = msgData;
            m_mutex.lock();
            m_msgInfos.enqueue(msg);
            m_mutex.unlock();
        }
    }
}

void MyMsgQueue::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    m_mutex.lock();
    if (m_msgInfos.isEmpty())
    {
        m_mutex.unlock();
        return;
    }

    InterModuleBus::Msg msg = m_msgInfos.dequeue();
    m_mutex.unlock();

    sendMsg(msg);
}
