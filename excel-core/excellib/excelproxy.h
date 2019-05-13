#ifndef EXCEL_PROXY_H
#define EXCEL_PROXY_H

#include <QStringList>

#include "excel-core_global.h"

class QVariant;
class QColor;

/*!
 * \brief The ExcelProxy class
 * excel操作代理类
 */
class EXCELCORESHARED_EXPORT ExcelProxy
{
public:
    ExcelProxy();
    ~ExcelProxy();

    Q_DISABLE_COPY(ExcelProxy)

public:
    /*!
     * \brief open 打开Excel
     * \param fileName
     * \return 成功返回true, 否则返回false
     */
    bool open(const QString &fileName);

    /*!
     * \brief sheetCount 获得sheet页的数量
     * \return
     */
    int sheetCount() const;

    /*!
     * \brief sheetNames 获得sheet页名字列表
     * \return
     */
    QStringList sheetNames() const;

    /*!
     * \brief currentSheetName 获取当前sheet页的名字
     * \return
     */
    QString currentSheetName() const;

    /*!
     * \brief changeSheet 根据名字切到某个sheet页
     * \param sheetName
     * \return 成功返回true, 否则返回false
     */
    bool changeSheet(const QString &sheetName);

    /*!
     * \brief changeSheet 根据索引切到某个sheet页
     * \param index 从1开始
     * \return 成功返回true, 否则返回false
     */
    bool changeSheet(int index);

    /*!
     * \brief rowCount 获得总行数
     * \return 失败返回-1
     */
    int rowCount() const;

    /*!
     * \brief colCount 获得总列数
     * \return 失败返回-1
     */
    int colCount() const;

    /*!
     * \brief cell 读某个单元格的内容
     * \param row 从1开始
     * \param col 从1开始
     * \return 返回对应的字符串
     */
    QString cell(int row, int col) const;

    /*!
     * \brief addSheet 添加sheet页
     * \param sheetName
     * \return 成功返回true, 否则返回false
     */
    bool addSheet(const QString &sheetName);

    /*!
     * \brief renameSheet 给sheet页重命名
     * \param oldName
     * \param newName
     * \return 成功返回true, 否则返回false
     */
    bool renameSheet(const QString &oldName, const QString &newName);

    /*!
     * \brief deleteSheet 删除某个sheet页
     * \param name
     * \return 成功返回true, 否则返回false
     */
    bool deleteSheet(const QString &name);

    /*!
     * \brief write 写单元格
     * \param row 从1开始
     * \param col 从1开始
     * \param value
     * \return 成功返回true, 否则返回false
     */
    bool write(int row, int col, const QVariant &value);

    /*!
     * \brief setTextColor 设置单元格字体颜色
     * \param row 从1开始
     * \param col 从1开始
     * \param color
     */
    void setTextColor(int row, int col, const QColor &color);

    /*!
     * \brief setBackgroundColor 设置单元格背景色
     * \param row 从1开始
     * \param col 从1开始
     * \param color
     */
    void setBackgroundColor(int row, int col, const QColor &color);

    /*!
     * \brief setFontSize 设置单元格字体大小
     * \param row 从1开始
     * \param col 从1开始
     * \param size
     */
    void setFontSize(int row, int col, int size);

    /*!
     * \brief setFontItalic 设置字体是否倾斜
     * \param row 从1开始
     * \param col 从1开始
     * \param italic
     */
    void setFontItalic(int row, int col, bool italic);

    /*!
     * \brief setFontBold 设置字体是否加粗
     * \param row
     * \param col
     * \param bold
     */
    void setFontBold(int row, int col, bool bold);

    /*!
     * \brief setTextWarp 设置自动换行
     * \param row 从1开始
     * \param col 从1开始
     * \param textWrap
     */
    void setTextWarp(int row, int col, bool textWrap);

    /*!
     * \brief setTextCenter 设置文字居中
     * \param row 从1开始
     * \param col 从1开始
     * \param center
     */
    void setTextCenter(int row, int col, bool center);

    /*!
     * \brief mergeCells 合并单元格
     * \param firstRow 从1开始
     * \param firstColumn 从1开始
     * \param lastRow 从1开始
     * \param lastColumn 从1开始
     * \return 成功返回true, 否则返回false
     */
    bool mergeCells(int firstRow, int firstColumn, int lastRow, int lastColumn);

    /*!
     * \brief save 保存文件
     * \return 成功返回true, 否则返回false
     */
    bool save() const;

    /*!
     * \brief saveAs 另存为
     * \param fileName
     * \return 成功返回true, 否则返回false
     */
    bool saveAs(const QString &fileName) const;

    /*!
     * \brief errMsg 返回错误信息,无错误返回空
     * \return
     */
    QString errMsg() const;

private:
    class Impl;
    Impl * const d_ptr;
};

#endif // EXCEL_PROXY_H
