#ifndef MSG_OBJ_DATA_H
#define MSG_OBJ_DATA_H

#include <QByteArray>
#include <QVariant>

namespace InterModuleBus {

struct Msg
{
    QString src;  // 消息源
    QString dst;  // 消息目的
    int type;     // 消息类型
    QVariant data; // 具体内容，  根据需要转成相应类型的数据 key  value（映射的key  映射的值）
};

} // InterModuleBus

struct StrIntMap
{
    QHash<QString, int> data;
};

Q_DECLARE_METATYPE(StrIntMap)

#endif // MSG_OBJ_DATA_H
