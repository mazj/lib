#include "baseexcelreader.h"


BaseExcelReader::BaseExcelReader()
    : m_sheetNames()
    , m_reader(0)
{
}

BaseExcelReader::~BaseExcelReader()
{
    readStop();
}

bool BaseExcelReader::read(const QString &fileName)
{
    if (!readStart(fileName))
    {
        return false;
    }

    dataClear();

    bool r = readDetails();

    readStop();

    return r;
}

void BaseExcelReader::dataClear()
{
    // 子类实现
}

QStringList BaseExcelReader::getSheetNames(const QString &fileName)
{
    QStringList names;

    if (readStart(fileName))
    {
        names = m_reader->sheetNames();
        readStop();
    }

    return names;
}

QStringList BaseExcelReader::getSheetNames()
{
    if (m_reader)
    {
        return m_reader->sheetNames();
    }

    return QStringList();
}

void BaseExcelReader::setSheetNames(const QStringList &sheetNames)
{
    m_sheetNames = sheetNames;
}

bool BaseExcelReader::readDetails()
{
    // 子类实现
    return false;
}

bool BaseExcelReader::readStart(const QString &fileName)
{
    if (fileName.isEmpty())
    {
        return false;
    }

    readStop();

    m_reader = new ExcelProxy();
    m_reader->open(fileName);

    dataClear();
    return true;
}

void BaseExcelReader::readStop()
{
    if (m_reader)
    {
        delete m_reader;
        m_reader = 0;
    }
}

bool BaseExcelReader::changeSheet(const QString &sheetName)
{
    if (!m_reader)
    {
        return false;
    }

    return m_reader->changeSheet(sheetName);
}

RangeData BaseExcelReader::getRange() const
{
    return RangeData(m_reader->rowCount(), m_reader->colCount());
}

int BaseExcelReader::getColumnIndex(const QString &columnName, int row) const
{
    int index = INVALUED_INDEX;

    if (!columnName.isEmpty())
    {
        const RangeData &data = getRange();

        // 读第一行，获得相应信息的列位置
        for (int i = data.firstColumn(); i <= data.lastColumn(); i++)
        {
            QString itemTitle = readString(row, i);
            if (columnName == itemTitle)
            {
                index = i;
                break;
            }
        }
    }

    return index;
}

QVariant BaseExcelReader::readCell(int row, int col) const
{
    if (row < 1 || col < 1)
    {
        return QVariant();
    }

    return m_reader->cell(row, col);
}

QString BaseExcelReader::readString(int row, int col) const
{
    return readCell(row, col).toString();
}

int BaseExcelReader::readInt(int row, int col, bool *ok) const
{
    return readCell(row, col).toInt(ok);
}

bool BaseExcelReader::isEmptyRow(int rowNum) const
{
    bool isEmpty = true;

    const RangeData &data = getRange();

    for (int i = data.firstColumn(); i <= data.lastColumn(); i++)
    {
        QString info = readString(rowNum, i);
        if (!info.isEmpty())
        {
            isEmpty = false;
            break;
        }
    }

    return isEmpty;
}

bool BaseExcelReader::isIndexInvalued(int index) const
{
    return INVALUED_INDEX == index;
}

QStringList BaseExcelReader::getLineInfo(int row) const
{
    QStringList lineInfos;

    for (int i = getRange().firstColumn(); i <= getRange().lastColumn(); i++)
    {
        lineInfos << readString(row, i);
    }

    return lineInfos;
}

RangeData::RangeData(int rowNums, int colNums)
    : m_rowNums(rowNums)
    , m_colNums(colNums)
{
}

int RangeData::firstRow() const
{
    return 1;
}

int RangeData::lastRow() const
{
    return m_rowNums;
}

int RangeData::firstColumn() const
{
    return 1;
}

int RangeData::lastColumn() const
{
    return m_colNums;
}
