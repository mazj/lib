#ifndef ABS_MSG_OBJ_H
#define ABS_MSG_OBJ_H

#include <QString>

#include "msgobjdata.h"

/*!
 * \brief The AbsMsgObj class
 * 模块间消息交互对象
 */
class AbsMsgObj
{
public:
    AbsMsgObj(const QString &key);
    virtual ~AbsMsgObj();

public:
    /*!
     * \brief getMsg 接口消息
     * \param msg 消息内容，具体格式需要各个模块自己定义好
     */
    virtual void getMsg(const InterModuleBus::Msg &msg) = 0;

    inline QString getModuleName() const
    {
        return m_key;
    }

private:
    QString m_key;
};

#endif // ABS_MSG_OBJ_H
