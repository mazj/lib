#include "hierarchicalheaderviewmodel.h"
#include "tabletreedata.h"

HierarchicalHeaderViewModel::HierarchicalHeaderViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

HierarchicalHeaderViewModel::~HierarchicalHeaderViewModel()
{
}

void HierarchicalHeaderViewModel::addHHeader(const TableTreeData &headerData)
{
    // 如果第一行为空，则忽略
    if (headerData.getColName().isEmpty())
    {
        int colNum = 0;
        for (TableTreeData *data : headerData.getChildrenDatas())
        {
            QStandardItem *colItem = new QStandardItem(data->getColName());
            m_horizontalHeaderModel.setItem(0, colNum++, colItem);

            addChildHeader(colItem, data->getChildrenDatas());
        }

        return;
    }

    QStandardItem *rootItem = new QStandardItem(headerData.getColName());
    m_horizontalHeaderModel.setItem(0, 0, rootItem);
    addChildHeader(rootItem, headerData.getChildrenDatas());
}

QVariant HierarchicalHeaderViewModel::data(const QModelIndex &index, int role) const
{
    if(HierarchicalHeaderView::HorizontalHeaderDataRole == role)
    {
        QVariant v;
        v.setValue((QObject*)&m_horizontalHeaderModel);
        return v;
    }

    if(HierarchicalHeaderView::VerticalHeaderDataRole == role)
    {
        QVariant v;
        v.setValue((QObject*)&m_verticalHeaderModel);
        return v;
    }

    return showData(index, role);
}

void HierarchicalHeaderViewModel::addChildHeader(QStandardItem *parentItem, const QList<TableTreeData *> &childrenHeader)
{
    for (TableTreeData *data : childrenHeader)
    {
        QStandardItem *childItem = new QStandardItem(data->getColName());
        addSubHeadColumn(parentItem, childItem);

        // 递归添加子表头
        addChildHeader(childItem, data->getChildrenDatas());
    }
}

void HierarchicalHeaderViewModel::addSubHeadColumn(QStandardItem *item, QStandardItem *subItem)
{
    if (!item || !subItem)
    {
        return;
    }

    QList<QStandardItem*> list;
    list << subItem;
    item->appendColumn(list);
}

void HierarchicalHeaderViewModel::addSubHeadColumn(QStandardItem *item, const QString &subItemName)
{
    QStandardItem *subItem =new QStandardItem(subItemName);
    addSubHeadColumn(item, subItem);
}
