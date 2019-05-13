#include "basexmlwriter.h"
#include "fileutils.h"

BaseXmlWriter::BaseXmlWriter()
    : m_writer()
    , m_file(0)
{
}

BaseXmlWriter::~BaseXmlWriter()
{
}

bool BaseXmlWriter::write(const QString &fileName)
{
    if (!initWrite(fileName))
    {
        return false;
    }

    bool r = writeDetails();

    deInitWrite();

    return r;
}

bool BaseXmlWriter::initWrite(const QString &fileName)
{
    m_file = FileUtils::fileOpen(fileName, false);
    if (!m_file)
    {
        return false;
    }

    m_writer.setDevice(m_file);
    m_writer.setAutoFormatting(true);
    m_writer.writeStartDocument();

    return true;
}

void BaseXmlWriter::deInitWrite()
{
    m_writer.writeEndDocument();

    FileUtils::fileClose(m_file);
}

void BaseXmlWriter::writeStartDocument()
{
    m_writer.writeStartDocument();
}

void BaseXmlWriter::writeStartElement(const QString &qualifiedName)
{
    m_writer.writeStartElement(qualifiedName);
}

void BaseXmlWriter::writeAttribute(const QString &qualifiedName, const QString &value)
{
    m_writer.writeAttribute(qualifiedName, value);
}

void BaseXmlWriter::writeAttributeIfNotNull(const QString &qualifiedName, const QString &value)
{
    if (!value.isEmpty())
    {
        writeAttribute(qualifiedName, value);
    }
}

void BaseXmlWriter::writeComment(const QString &text)
{
    m_writer.writeComment(text);
}

void BaseXmlWriter::writeCommentIfNotNull(const QString &text)
{
    if (!text.isEmpty())
    {
        writeComment(text);
    }
}

void BaseXmlWriter::writeEndElement()
{
    m_writer.writeEndElement();
}

void BaseXmlWriter::writeEndDocument()
{
    m_writer.writeEndDocument();
}
