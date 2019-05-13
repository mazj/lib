#include <QStringList>
#include <QSize>
#include <QColor>

#include "datapointitemmodel.h"

DataPointItemModel::DataPointItemModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_headerDatas()
    , m_datas()
{
}

int DataPointItemModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_datas.size();
}

int DataPointItemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_headerDatas.isEmpty())
    {
        return 0;
    }

    return m_headerDatas.size();
}

QVariant DataPointItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter| Qt::AlignVCenter);
    }

    if (Qt::TextColorRole == role)
    {
        if (index.row() < m_datas.size() && index.column() < m_datas[index.row()].size())
        {
            return QVariant(m_datas[index.row()].at(index.column()).getTextColor());
        }

        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        if (index.row() < m_datas.size() && index.column() < m_datas[index.row()].size())
        {
            return m_datas[index.row()].at(index.column()).data();
        }
    }

    return QVariant();
}

QVariant DataPointItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // 横向标题
    if (orientation == Qt::Horizontal
            && role == Qt::DisplayRole
            && section < m_headerDatas.count())
    {
        return  m_headerDatas.at(section);
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

bool DataPointItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
    {
        return QAbstractTableModel::setData(index, value, role);
    }

    int row = index.row();
    int col = index.column();

    if (row >= m_datas.size() || col >= m_datas[row].size())
    {
        return false;
    }


    DataPointItem &item = m_datas[row][col];
    item.setShowText(value.toString());

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags DataPointItemModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.isValid())
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

void DataPointItemModel::setHeader(const QStringList &header)
{
    if (header.isEmpty() || m_headerDatas == header)
    {
        return;
    }

    // 当表格头变化时，意味着在执行新的案例，重置所有信息
    beginResetModel();
    m_datas.clear();
    m_headerDatas = header;
    endResetModel();
}

void DataPointItemModel::addData(const DataPointItem &data)
{
    int rowIndex = rowCount(QModelIndex());
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);

    if (m_datas.isEmpty())
    {
        addNewLine(data);
    }
    else
    {
        QList<DataPointItem> &lineDatas = m_datas.last();
        if (lineDatas.size() == m_headerDatas.size())
        {
            // new line
            addNewLine(data);
        }
        else
        {
            lineDatas << data;
        }
    }

    endInsertRows();
}

void DataPointItemModel::clearDatas()
{
    beginResetModel();
    m_headerDatas.clear();
    m_datas.clear();
    endResetModel();
}

void DataPointItemModel::refresh()
{
    beginResetModel();
    endResetModel();
}

void DataPointItemModel::writeMemory(bool isFirstTime)
{
    for (int i = 0; i < m_datas.size(); i++)
    {
        for (int j = 0; j < m_datas[i].size(); j++)
        {
            m_datas[i][j].writeMemory(isFirstTime);
        }
    }

    // 写完后刷新一下界面
    refresh();
}

void DataPointItemModel::addNewLine(const DataPointItem &data)
{
    QList<DataPointItem> lineDatas;
    lineDatas << data;

    m_datas << lineDatas;
}
