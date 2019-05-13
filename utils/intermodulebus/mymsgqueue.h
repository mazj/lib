#ifndef MY_MSG_QUEUE_H
#define MY_MSG_QUEUE_H

#include <QObject>
#include <QHash>
#include <QSet>
#include <QQueue>
#include <QMutex>

#include "msgobjdata.h"

class AbsMsgObj;


class MyMsgQueue : public QObject
{
    Q_OBJECT

public:
    MyMsgQueue(QObject *parent=Q_NULLPTR);

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
     * \param isAsync 是否为异步发送
     * \return
     */
    bool sendMsg(const QString &dst, int type, const QVariant &msgData, bool isAsync);

    /*!
     * \brief sendMsg 发送消息到指定的模块
     * \param dstList 可以指定多个地址
     * \param type
     * \param msgData
     * \param isAsync 是否为异步发送
     * \return
     */
    bool sendMsg(const QStringList &dstList, int type, const QVariant &msgData, bool isAsync);

    /*!
     * \brief broadcastMsg
     * 将消息发送到除发送模块之外的所有注册模块
     * \param type
     * \param msgData
     */
    void broadcastMsg(const int type, const QVariant &msgData, const QString &srcModuleName);

private:

    virtual void timerEvent(QTimerEvent *event) override;

    /*!
     * \brief sendMsg 发送消息到指定的模块
     * \param msg
     * \return 成功返回true
     */
    bool sendMsg(const InterModuleBus::Msg &msg);


private:
    QMutex m_mutex;

    QHash<QString, QSet<AbsMsgObj*> > m_msgObjs; // key:msgObjKey, value:msgObj list 去重

    QQueue<InterModuleBus::Msg> m_msgInfos;
};


#endif // MY_MSG_QUEUE_H
