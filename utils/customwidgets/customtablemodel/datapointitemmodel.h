#ifndef DATA_POINT_ITEM_MODEL_H
#define DATA_POINT_ITEM_MODEL_H

#include <QAbstractTableModel>

#include "datapointitem.h"

/*!
 * \brief The DataPointItemModel class
 * 自定义TableModel，适合行列数据固定，但是值一直变化的情况
 */
class DataPointItemModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataPointItemModel(QObject *parent = Q_NULLPTR);

public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*!
     * \brief setHeader 设置表头
     * \param header
     */
    void setHeader(const QStringList &header);

    /*!
     * \brief addData 添加数据
     * \param data 具体数据
     */
    void addData(const DataPointItem &data);

    void clearDatas();

    /*!
     * \brief refresh 刷新界面
     */
    void refresh();

    /*!
     * \brief writeMemory 将单元格中的内容写到关联的内存地址中去
     */
    void writeMemory(bool isFirstTime);

private:
    void addNewLine(const DataPointItem &data);

private:
    QStringList m_headerDatas;
    QList<QList<DataPointItem> > m_datas;
};

#endif // DATA_POINT_ITEM_MODEL_H
