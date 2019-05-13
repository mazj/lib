#ifndef BASE_XML_WRITER_H
#define BASE_XML_WRITER_H

#include <QXmlStreamWriter>


class QFile;

class BaseXmlWriter
{
public:
    BaseXmlWriter();
    virtual ~BaseXmlWriter();

public:
    bool write(const QString &fileName);

protected:
    bool initWrite(const QString &fileName);
    void deInitWrite();

    virtual bool writeDetails() = 0;

    void writeStartDocument();
    void writeStartElement(const QString &qualifiedName);
    void writeAttribute(const QString &qualifiedName, const QString &value);
    void writeAttributeIfNotNull(const QString &qualifiedName, const QString &value);
    void writeComment(const QString &text);
    void writeCommentIfNotNull(const QString &text);
    void writeEndElement();
    void writeEndDocument();

protected:
    QXmlStreamWriter m_writer;

private:
    QFile *m_file;
};

#endif // BASE_XML_WRITER_H
