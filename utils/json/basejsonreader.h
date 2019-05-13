#ifndef BASE_JSON_READER_H
#define BASE_JSON_READER_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class BaseJsonReader
{
public:
    virtual ~BaseJsonReader();

public:
    bool read(const QString &fileName);
    virtual void dataClear() = 0;

protected:
    virtual bool readDetails(const QJsonObject &obj) = 0;
};

#endif // BASE_JSON_READER_H
