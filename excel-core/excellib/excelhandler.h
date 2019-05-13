#ifndef EXCELHANDLER_H
#define EXCELHANDLER_H

#include <QStringList>
#include <QVariant>

#include "excel-core_global.h"

class EXCELCORESHARED_EXPORT CExcelHandler
{
public:
    static CExcelHandler &GetInstance();

public:
    //取得行的总数
    int GetRowCount() const;
    //取得列的总数
    int GetColumnCount() const;
    //得到Sheet的总数
    int GetSheetCount() const;
    //取得打开文件的名称
    QString GetOpenExcelName() const;
    //取得打开sheet的名称
    QString GetLoadSheetName() const;
    // 返回所有sheet页的名称
    QStringList GetSheetNames() const;

    //得到一个CELL的信息
    QVariant GetCellInfo(int iRow, int iColumn) const;
    //通过索引使用某个sheet
    bool LoadSheetByIndex(int iIndex,bool pre_load);
    //通过名称使用某个sheet
    bool LoadSheetByName(QString qstr_SheetName,bool pre_load);

    //删除特定Sheet页
    bool DeleteSheet(int iIndex);
    //添加特定Sheet页
    bool AddSheet(QString qstr_SheetName);
    //修改Sheet页名称
    bool RenameSheet(int iIndex,QString qstr_SheetName);
    //写入一个CELL数据
    bool SetCellData(int iRow, int iColumn, QVariant new_Data);
    //写入一个区域数据, iSRow, iSColNum都是从0开始
    bool SetRangeData(int iSRow,int iSColumn,const QList<QList<QVariant> > &ListCell);


    //保存Excel文件
    void SaveXlsFile();
    //另存为一个EXCEL文件
    void SaveAsXlsFile(const QString qstr_XlsFile);
    //打开文件
    bool OpenExcelFile(const QString qstr_FileName);
    //关闭打开的Excel 文件，有时候打开EXCEL文件就要
    void CloseExcelFile(bool bSave = false);

    //文字居中
    bool SetCellTextCenter(int iRow,int iCol);
    //设置黑体
    bool SetCellFontBold(int iRow,int iCol,bool bIsBold);
    //自动换行
    bool SetCellTextWrap(int iRow,int iCol,bool bIsWrap);
    //设置字体大小
    bool SetCellFontSize(int iRow,int iCol,int iFontSize);
    //合并单元格
    bool MergeCell(int iSRow,int iSCol,int iRowNum,int iColNum);

private:
    CExcelHandler();
    ~CExcelHandler();

    Q_DISABLE_COPY(CExcelHandler)

private:
    class Impl;
    Impl * const d_ptr;
};

#endif // EXCELHANDLER_H
