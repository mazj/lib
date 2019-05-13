#ifndef BASE_EXCEL_READER_H
#define BASE_EXCEL_READER_H

#include <QVariant>

#include "excelproxy.h"

const int INVALUED_INDEX = -1;

class RangeData
{
public:
    RangeData(int rowNums, int colNums);

public:
    int firstRow() const;
    int lastRow() const;
    int firstColumn() const;
    int lastColumn() const;

private:
    int m_rowNums;
    int m_colNums;
};

class BaseExcelReader
{
public:
    BaseExcelReader();
    virtual ~BaseExcelReader();

public:
    /*!
     * \brief read 读excel文件，解析
     * \param fileName
     * \return
     */
    bool read(const QString &fileName);

    /*!
     * \brief dataClear 情况存储的内容
     */
    virtual void dataClear();

    /*!
     * \brief getSheetNames 获得所有sheet页名字
     * \param fileName
     * \return
     */
    QStringList getSheetNames(const QString &fileName);

    QStringList getSheetNames();

    /*!
     * \brief setSheetNames 设置需要读的sheet页名字
     * \param sheetNames
     */
    void setSheetNames(const QStringList &sheetNames);

protected:
    /*!
     * \brief readDetails 子类实现具体的读操作
     * \return
     */
    virtual bool readDetails();

    /*!
     * \brief changeSheet 切换工作表
     * \param sheetName
     * \return
     */
    bool changeSheet(const QString &sheetName);

    /*!
     * \brief getRange 获得行列信息
     * \return
     */
    RangeData getRange() const;

    /*!
     * \brief getColumnIndex 获得对应列名的列号
     * \param columnName
     * \return 失败返回-1
     */
    int getColumnIndex(const QString &columnName, int row=0) const;

    /*!
     * \brief readCell 读单元格
     * \param row
     * \param col
     * \return
     */
    QVariant readCell(int row, int col) const;

    /*!
     * \brief readString 读单元格，返回QString类型数据
     * \param row
     * \param col
     * \return
     */
    QString readString(int row, int col) const;

    /*!
     * \brief readInt 读单元格，返回int类型数据
     * \param row
     * \param col
     * \param ok
     * \return
     */
    int readInt(int row, int col, bool *ok = Q_NULLPTR) const;

    /*!
     * \brief isEmptyRow 判断是否为空行
     * \param rowNum
     * \return
     */
    bool isEmptyRow(int rowNum) const;

    /*!
     * \brief isIndexInvalued 判断当前索引是否有效
     * \param index
     * \return
     */
    bool isIndexInvalued(int index) const;

    /*!
     * \brief getLineInfo 返回一行的信息
     * \param row
     * \return
     */
    QStringList getLineInfo(int row) const;

private:
    /*!
     * \brief readStart 读excel之前做的初始化操作
     * \param fileName
     * \return
     */
    bool readStart(const QString &fileName);

    /*!
     * \brief readStop 读之后做的反初始化操作
     */
    void readStop();

protected:
    QStringList m_sheetNames;

private:
    ExcelProxy *m_reader;
};

#endif // BASE_EXCEL_READER_H
