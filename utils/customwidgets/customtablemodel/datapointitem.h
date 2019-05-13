#ifndef DATA_POINT_ITEM_H
#define DATA_POINT_ITEM_H

#include <QString>
#include <QMap>
#include <QColor>


class DataPointItem
{
public:
    enum Type {
        T_STRING = 1024,
        T_CHARARRAY,
        T_INT64,
        T_UINT64,
        T_INT32,
        T_UINT32,
        T_INT16,
        T_UINT16,
        T_INT8,
        T_UINT8,
        T_FLOAT,
        T_DOUBLE,
        T_VERSION_INFO, // 版本信息
    };

public:
    /*!
     * \brief DataPointItem
     * \param dataAddr 内存地址
     * \param dataType 数据类型
     * \param defaultValue 默认值
     */
    DataPointItem(void *dataAddr,
                  Type dataType,
                  const QMap<QString, QString> &mapData = QMap<QString, QString>(),
                  const QString &defaultValue="");

public:
    /*!
     * \brief data 读内存数据，返回字符串
     * \return
     */
    QString data() const;

    /*!
     * \brief setShowText 设置用户修改的数据
     * \param text
     */
    void setShowText(const QString &text);

    /*!
     * \brief writeMemory 将m_showText数据写内存
     */
    void writeMemory(bool isFirstTime=false);

    QColor getTextColor() const;

private:
    /*!
     * \brief getMemoryValue 获取内存中的值
     * \return
     */
    QString getMemoryValue() const;

    QString getStrVersion(quint32 value) const;
    quint32 getIntVersion(const QString &value);


private:
    void *m_dataAddr; // 保存数据的地址
    Type m_dataType;  // 保存数据类型
    QMap<QString, QString> m_dataMap; // 数据映射
    QString m_defaultValue; // 默认值
    QString m_showText; // 用户修改时，需要显示的数据，当用户点确认修改时，才将m_showText数据真正写内存
    QColor m_textColor;
};

#endif // DATA_POINT_ITEM_H
