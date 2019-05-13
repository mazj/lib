#ifndef BASE_XML_READER_H
#define BASE_XML_READER_H

#include <QXmlStreamReader>

class QFile;

class BaseXmlReader
{
public:
    BaseXmlReader();
    virtual ~BaseXmlReader();

public:
    /*!
     * \brief read 读xmlwen文件
     * \param fileName
     * \return
     */
    bool read(const QString &fileName);

    /*!
     * \brief dataClear 数据清空，避免重复读一个文件时导致数据重复
     */
    virtual void dataClear() = 0;

protected:
    /*!
     * \brief readDetails 读具体内容
     * \return
     */
    virtual bool readDetails() = 0;

    bool readNextStartElement();
    void skipCurrentElement();
    QString getCurrentElementName();
    void raiseError(const QString& message = QString());
    QString getAttrValue(const QString &attrName);

private:
    bool readStart(const QString &fileName);
    bool readStop();

protected:
    QXmlStreamReader m_reader;

private:
    QFile *m_file;
};

#endif // BASE_XML_READER_H
