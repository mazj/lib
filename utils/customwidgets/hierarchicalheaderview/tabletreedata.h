#ifndef TABLE_TREE_DATA_H
#define TABLE_TREE_DATA_H

#include <QList>

class TableTreeData
{
public:
    TableTreeData(const QString &name="");
    ~TableTreeData();

public:
    QList<TableTreeData *>& operator<<(TableTreeData *child);

    const QList<TableTreeData *>& getChildrenDatas() const;

    QString getColName() const;

private:
    QString m_colName;
    QList<TableTreeData *> m_children;
};

#endif // TABLE_TREE_DATA_H
