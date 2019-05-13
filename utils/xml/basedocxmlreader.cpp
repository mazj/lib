#include "basedocxmlreader.h"
#include "fileutils.h"

BaseDocXmlReader::BaseDocXmlReader()
{

}

BaseDocXmlReader::~BaseDocXmlReader()
{

}

bool BaseDocXmlReader::read(const QString &fileName)
{
    if (!readStart(fileName))
    {
        return false;
    }

    bool r = readDetails();

    clearDomEles();

    return readStop() && r;
}

bool BaseDocXmlReader::isExistNodeTagName(const QString& tagName)
{
    if(!m_mapDomElement[tagName].isNull() && tagName == m_mapDomElement[tagName].tagName())
        return true;
    else
        return false;
}

void BaseDocXmlReader::pushFirstTopElement(const QString &tagName)
{
    m_firstDomElement[tagName] = m_mapDomElement[tagName];
}

void BaseDocXmlReader::popFirstTopElement(const QString &tagName)
{
    m_mapDomElement[tagName] = m_firstDomElement[tagName];
}

void BaseDocXmlReader::nextSiblingElement(const QString &tagName)
{
     m_mapDomElement[tagName] =  m_mapDomElement[tagName].nextSiblingElement();
}

QString BaseDocXmlReader::getStrTagName(const QString &tagName)
{
    return m_mapDomElement[tagName].tagName();
}

QString BaseDocXmlReader::getStrText(const QString &tagName)
{
    return  m_mapDomElement[tagName].text();
}

QString BaseDocXmlReader::getStrAttribute(const QString &tagName, const QString &strAttr)
{
    if(! m_mapDomElement[tagName].hasAttribute(strAttr))
        return "";
    else
        return  m_mapDomElement[tagName].attribute(strAttr);
}

bool BaseDocXmlReader::isExistRootTagName(const QString &strRoot)
{
    m_mapDomElement[strRoot] = m_pDoc->documentElement();
    if(!m_mapDomElement[strRoot].isNull() && strRoot == m_mapDomElement[strRoot].tagName())
        return true;
    else
        return false;
}

void BaseDocXmlReader::firstChildElement(const QString& oldTagName, const QString &newTagName)
{
    m_mapDomElement[newTagName] = m_mapDomElement[oldTagName].firstChildElement();
}

QString BaseDocXmlReader::findFirstChildTag(const QString &strTagName)
{
    return m_mapDomElement[strTagName].firstChildElement().tagName();
}

bool BaseDocXmlReader::setContent(QFile *file)
{
    QString strError = "";
    int row = 0;
    int column = 0;
    if(!m_pDoc->setContent(file, true, &strError, &row, &column))
    {
        qDebug() << "errInfo: "<< strError << "line: " << row << "col: " << column;
        return false;
    }
    return true;
}

bool BaseDocXmlReader::readStart(const QString &fileName)
{
    m_pDoc = new QDomDocument();
    if(!m_pDoc)
        return false;

    m_file = FileUtils::fileOpen(fileName, QIODevice::ReadOnly);
    if (!m_file)
        return false;

    if(!setContent(m_file))
        return false;

    dataClear();
    return true;
}

bool BaseDocXmlReader::readStop()
{
    FileUtils::fileClose(m_file);

    if(m_pDoc)
    {
        delete m_pDoc;
        m_pDoc = NULL;
    }

    return true;
}

void BaseDocXmlReader::clearDomEles()
{
    m_mapDomElement.clear();
}

quint16 BaseDocXmlReader::getIntAttribute(const QString& tagName, const QString& strAttr)
{
    if(!m_mapDomElement[tagName].hasAttribute(strAttr))
        return 0;
    else
        return m_mapDomElement[tagName].attribute(strAttr).toUShort();
}
