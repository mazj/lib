#include "basexmlreader.h"
#include "fileutils.h"

BaseXmlReader::BaseXmlReader()
    : m_file(0)
{
}

BaseXmlReader::~BaseXmlReader()
{
}

bool BaseXmlReader::read(const QString &fileName)
{
    if (!readStart(fileName))
    {
        return false;
    }

    bool r = readDetails();

    return readStop() && r;
}

bool BaseXmlReader::readStart(const QString &fileName)
{
    m_file = FileUtils::fileOpen(fileName);
    if (!m_file)
    {
        return false;
    }

    m_reader.setDevice(m_file);
    dataClear();

    return true;
}

bool BaseXmlReader::readStop()
{
    FileUtils::fileClose(m_file);

    return !m_reader.error();
}

bool BaseXmlReader::readNextStartElement()
{
    return m_reader.readNextStartElement();
}

void BaseXmlReader::skipCurrentElement()
{
    m_reader.skipCurrentElement();
}

QString BaseXmlReader::getCurrentElementName()
{
    return m_reader.name().toString();
}

void BaseXmlReader::raiseError(const QString &message)
{
    m_reader.raiseError(message);
}

QString BaseXmlReader::getAttrValue(const QString &attrName)
{
    if (!m_reader.attributes().hasAttribute(attrName))
    {
        return "";
    }

    return m_reader.attributes().value(attrName).toString();
}
