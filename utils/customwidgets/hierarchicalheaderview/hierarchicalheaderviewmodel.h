#include <QAbstractTableModel>
#include <QStandardItemModel>

#include "hierarchicalheaderview.h"

class TableTreeData;

class HierarchicalHeaderViewModel : public QAbstractTableModel
{
public:
    HierarchicalHeaderViewModel(QObject* parent=0);
    virtual ~HierarchicalHeaderViewModel();

public:
    void addHHeader(const TableTreeData &headerData);

    virtual int rowCount(const QModelIndex &parent) const = 0;
    virtual int columnCount(const QModelIndex &parent) const = 0;

    QVariant data(const QModelIndex &index, int role) const;

protected:
    /*!
     * \brief addChildHeader 添加子表头
     * \param colItem
     * \param childrenHeader
     */
    void addChildHeader(QStandardItem *parentItem, const QList<TableTreeData *> &childrenHeader);

    /*!
     * \brief showData 显示表格内容
     * \param index
     * \param role
     * \return
     */
    virtual QVariant showData(const QModelIndex &index, int role) const = 0;

    /*!
     * \brief addSubHeadColumn 对表头元素添加子列
     * \param item
     * \param subItem
     */
    void addSubHeadColumn(QStandardItem *item, QStandardItem *subItem);
    void addSubHeadColumn(QStandardItem *item, const QString &subItemName);

protected:
    QStandardItemModel m_horizontalHeaderModel;
    QStandardItemModel m_verticalHeaderModel;
};
