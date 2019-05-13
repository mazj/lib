#ifndef INTER_MODULE_MSG_MGR_H
#define INTER_MODULE_MSG_MGR_H

#include <QObject>
#include <QVariant>

#include "singletonutils.h"

class AbsMsgObj;
class MyMsgQueue;


#define g_msgq InterModuleMsgMgr::instance()


/*!
 * \brief The InterModuleMsgMgr class
 * 模块间数据交换管理类, 单例
 */
class InterModuleMsgMgr : public QObject
{
    Q_OBJECT

    DECLARE_SINGLETON(InterModuleMsgMgr)

public:
    ~InterModuleMsgMgr();

public:
    /*!
     * \brief msgObjRegister 消息对象注册
     * \param key
     * \param msgObj
     */
    void msgObjRegister(const QString &key, AbsMsgObj *msgObj);

    /*!
     * \brief msgObjUnregister 消息对象反注册
     * \param key
     * \param msgObj
     */
    void msgObjUnregister(const QString &key, AbsMsgObj *msgObj);

    /*!
     * \brief sendMsg 发送消息到指定的模块
     * \param dst
     * \param type
     * \param msgData
     * \param isAsync 默认异步发送
     * \return
     */
    bool sendMsg(const QString &dst, int type, const QVariant &msgData=QVariant(), bool isAsync=true);

    /*!
     * \brief sendMsg 发送消息到指定的模块
     * \param dstList 可以指定多个地址
     * \param type
     * \param msgData
     * \param isAsync 默认异步发送, 注意， 如果需要在getMsg()中调用sengMsg, 需要指定为同步模式，否则出现死锁问题
     * \return
     */
    bool sendMsg(const QStringList &dstList, int type, const QVariant &msgData=QVariant(), bool isAsync=true);

    /*!
     * \brief broadcastMsg
     * 将消息发送到除发送模块之外的所有注册模块
     * \param type
     * \param msgData
     */
    void broadcastMsg(const int type, const QVariant &msgData, const QString &srcModuleName);

private:
    InterModuleMsgMgr(QObject *parent=Q_NULLPTR);

private:
    QThread *m_thread;
    MyMsgQueue *m_msgq;
};

#endif // INTER_MODULE_MSG_MGR_H
