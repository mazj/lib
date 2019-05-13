#include "datapointitem.h"

static const QString INVALUED_SHOW_TEXT = "0;s_i#m$pl?e1";

DataPointItem::DataPointItem(void *dataAddr, Type dataType, const QMap<QString, QString> &mapData, const QString &defaultValue)
    : m_dataAddr(dataAddr)
    , m_dataType(dataType)
    , m_dataMap(mapData)
    , m_defaultValue(defaultValue)
    , m_showText(INVALUED_SHOW_TEXT)
    , m_textColor(Qt::white)
{
}

QString DataPointItem::data() const
{
    // 如果是用户自己修改的数据，则显示修改的数据，否则读内存中的数据
    if (m_showText != INVALUED_SHOW_TEXT)
    {
        return m_showText;
    }

    return getMemoryValue();
}

void DataPointItem::setShowText(const QString &text)
{
    m_showText = text;
    m_textColor = (text == getMemoryValue() ? Qt::white : Qt::red);
}

void DataPointItem::writeMemory(bool isFirstTime)
{
    if (isFirstTime)
    {
        if (m_defaultValue.isEmpty())
        {
            return;
        }

        m_showText = m_defaultValue;
    }
    else
    {
        if (INVALUED_SHOW_TEXT == m_showText|| getMemoryValue() == m_showText)
        {
            return;
        }
    }

    QString value = m_showText;

    m_textColor = Qt::white;

    if (m_dataMap.values().contains(value))
    {
        value = m_dataMap.key(m_showText);
    }

    switch (m_dataType)
    {
    case T_STRING:
        *(QString *)m_dataAddr = value;
        break;
    case T_CHARARRAY:
        memcpy(m_dataAddr, value.toStdString().c_str(), value.toStdString().length());
        break;
    case T_INT64:
        *(qint64 *)m_dataAddr = value.toLongLong();
        break;
    case T_UINT64:
        *(quint64 *)m_dataAddr = value.toULongLong();
        break;
    case T_INT32:
        *(qint32 *)m_dataAddr = value.toInt();
        break;
    case T_UINT32:
        *(quint32 *)m_dataAddr = value.toUInt();
        break;
    case T_INT16:
        *(qint16 *)m_dataAddr = value.toShort();
        break;
    case T_UINT16:
        *(quint16 *)m_dataAddr = value.toUShort();
        break;
    case T_INT8:
        *(char *)m_dataAddr = value.toInt();
        break;
    case T_UINT8:
        *(quint8 *)m_dataAddr = value.toInt();
        break;
    case T_VERSION_INFO:
        *(quint32 *)m_dataAddr = getIntVersion(value);
        break;
    default:
        break;
    }
}

QColor DataPointItem::getTextColor() const
{
    return m_textColor;
}

QString DataPointItem::getMemoryValue() const
{
    QString value;

    switch (m_dataType)
    {
    case T_STRING:
        value = *(QString *)m_dataAddr;
        break;
    case T_CHARARRAY:
        value = QString((char *)m_dataAddr);
        break;
    case T_INT64:
        value = QString::number(*(qint64 *)m_dataAddr);
        break;
    case T_UINT64:
        value = QString::number(*(quint64 *)m_dataAddr);
        break;
    case T_INT32:
        value = QString::number(*(qint32 *)m_dataAddr);
        break;
    case T_UINT32:
        value = QString::number(*(quint32 *)m_dataAddr);
        break;
    case T_INT16:
        value = QString::number(*(qint16 *)m_dataAddr);
        break;
    case T_UINT16:
        value = QString::number(*(quint16 *)m_dataAddr);
        break;
    case T_INT8:
        value = *(char *)m_dataAddr;
        break;
    case T_UINT8:
        value = QString::number(*(quint8 *)m_dataAddr);
        break;
    case T_VERSION_INFO:
        value = getStrVersion(*(quint32 *)m_dataAddr);
        break;
    default:
        value = "";
        break;
    }

    if (!m_dataMap.isEmpty())
    {
        value = m_dataMap.value(value, "");
    }

    // 当取不到数据时，用默认值
    if (value.isEmpty())
    {
        value = m_defaultValue;
    }

    return value;
}

QString DataPointItem::getStrVersion(quint32 value) const
{
    QString valueStr;

    valueStr += QString::number(value >> 24 & 0x000F);
    valueStr += ".";
    valueStr += QString::number((value >> 16) & 0x000F);
    valueStr += ".";
    valueStr += QString::number((value >> 8) & 0x000F);
    valueStr += ".";
    valueStr += QString::number((value) & 0x000F);

    return valueStr;
}

quint32 DataPointItem::getIntVersion(const QString &value)
{
    quint32 result = 0;

    QString strVersion = value.trimmed();
    if(strVersion.contains("V"))
    {
        strVersion = strVersion.right(strVersion.length()-1);
    }

    QStringList listVersion = strVersion.split(".");
    int len = listVersion.length() - 1;

    for (QString strNum : listVersion)
    {
        quint32 num = strNum.toUInt();
        result += num * (1 << (8*len));
        len--;
    }

    return result;
}
