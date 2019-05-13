#include "tabletreedata.h"

TableTreeData::TableTreeData(const QString &name)
    : m_colName(name)
    , m_children()
{
}

TableTreeData::~TableTreeData()
{
    // delete all children
    for (TableTreeData *data : m_children)
    {
        //qDebug() << "delete" << data->m_colName;
        delete data;
    }
}

QList<TableTreeData *> &TableTreeData::operator<<(TableTreeData *child)
{
    if (child)
    {
        m_children.append(child);
    }

    return m_children;
}

const QList<TableTreeData *> &TableTreeData::getChildrenDatas() const
{
    return m_children;
}

QString TableTreeData::getColName() const
{
    return m_colName;
}
