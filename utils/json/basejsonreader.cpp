#include <QFile>

#include "basejsonreader.h"

BaseJsonReader::~BaseJsonReader()
{
}

bool BaseJsonReader::read(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        return false;
    }

    dataClear();

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject obj = loadDoc.object();

    readDetails(obj);

    file.close();

    return true;
}
