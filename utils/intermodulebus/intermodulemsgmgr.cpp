#include <QThread>

#include "intermodulemsgmgr.h"
#include "mymsgqueue.h"
#include "absmsgobj.h"

InterModuleMsgMgr::~InterModuleMsgMgr()
{
    m_msgq->deleteLater();

    // free thread
    {
        m_thread->quit();
        m_thread->wait(1000);
        if (!m_thread->isFinished())
        {
            m_thread->terminate();
        }
        delete m_thread;
    }
}

void InterModuleMsgMgr::msgObjRegister(const QString &key, AbsMsgObj *msgObj)
{
    m_msgq->msgObjRegister(key, msgObj);
}

void InterModuleMsgMgr::msgObjUnregister(const QString &key, AbsMsgObj *msgObj)
{
    m_msgq->msgObjUnregister(key, msgObj);
}

bool InterModuleMsgMgr::sendMsg(const QString &dst, int type, const QVariant &msgData, bool isAsync)
{
    return m_msgq->sendMsg(dst, type, msgData, isAsync);
}

bool InterModuleMsgMgr::sendMsg(const QStringList &dstList, int type, const QVariant &msgData, bool isAsync)
{
    return m_msgq->sendMsg(dstList, type, msgData, isAsync);
}

void InterModuleMsgMgr::broadcastMsg(const int type, const QVariant &msgData, const QString &srcModuleName)
{
    m_msgq->broadcastMsg(type, msgData, srcModuleName);
}

InterModuleMsgMgr::InterModuleMsgMgr(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread)
    , m_msgq(new MyMsgQueue)
{
    m_thread->start();

    m_msgq->moveToThread(m_thread);
}
