#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

#include "fileutils.h"

QString FileUtils::s_lastDir = ".";

QString FileUtils::getFilePath(const QString &title, const QString &type, bool isOpen)
{
    QString path;
    if (isOpen)
    {
        path = QFileDialog::getOpenFileName(NULL, title, s_lastDir, type);
    }
    else
    {
        path = QFileDialog::getSaveFileName(NULL, title, s_lastDir, type);
    }

    s_lastDir = getDir(path);

    return path;
}

QString FileUtils::getOpenFilePath(const QString &title, const QString &type)
{
    return getFilePath(title, type, true);
}

QString FileUtils::getSaveFilePath(const QString &title, const QString &type)
{
    return getFilePath(title, type, false);
}

QString FileUtils::getSaveXmlFilePath(const QString &title)
{
    return getSaveFilePath(title, "XML Files(*.xml)");
}

QString FileUtils::getSaveWordFilePath(const QString &title)
{
    return getSaveFilePath(title, "Word Files(*.docx)");
}

QString FileUtils::getOpenExcelFilePath(const QString &title)
{
    return getOpenFilePath(title, "Excel Files(*.xlsx)");
}

QString FileUtils::getOpenIniFilePath(const QString &title)
{
    return getOpenFilePath(title, "INI Files(*.ini)");
}

QString FileUtils::getOpenXmlFilePath(const QString &title)
{
    return getOpenFilePath(title, "XML Files(*.xml)");
}

QString FileUtils::getOpenTxtFilePath(const QString &title)
{
    return getOpenFilePath(title, "TXT Files(*.txt)");
}

QString FileUtils::getOpenFilePath(const QString &title, int type)
{
    QString path;

    switch (type)
    {
    case FILE_TYPE_XML:
        path = getOpenXmlFilePath(title);
        break;
    case FILE_TYPE_TXT:
        path = getOpenTxtFilePath(title);
        break;
    case FILE_TYPE_INI:
        path = getOpenIniFilePath(title);
        break;
    case FILE_TYPE_EXCEL:
        path = getOpenExcelFilePath(title);
        break;
    default:
        path = "";
        break;
    }

    return path;
}

QFile *FileUtils::fileOpen(const QString &path, bool isRead)
{
    QIODevice::OpenMode mode = isRead ? QIODevice::ReadOnly : QIODevice::WriteOnly;
    mode |= QIODevice::Text;

    QFile *file = new QFile(path);
    if (!file->open(mode))
    {
        QString errMsg = "Cannot open file:\n" + path;
        QMessageBox::warning(NULL, "Read File", errMsg);
        return 0;
    }

    return file;
}

QFile *FileUtils::fileOpen(const QString &title, const QString &type, bool isRead)
{
    QString path = isRead ? getOpenFilePath(title, type) : getSaveFilePath(title, type);
    if(path.isEmpty())
    {
        return 0;
    }

    return fileOpen(path, isRead);
}

QFile *FileUtils::fileRead(const QString &title, const QString &type)
{
    return fileOpen(title, type, true);
}

QFile *FileUtils::fileWrite(const QString &title, const QString &type)
{
    return fileOpen(title, type, false);
}

QFile *FileUtils::fileTxtRead(const QString &title)
{
    return fileRead(title, "TXT Files(*.txt)");
}

QFile *FileUtils::fileXmlRead(const QString &title)
{
    return fileRead(title, "XML Files(*.xml)");
}

bool FileUtils::writeTxtFile(const QString &fileName, const QString &fileInfo)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << fileInfo;

        file.close();
        return true;
    }

    return false;
}

void FileUtils::fileClose(QFile *file)
{
    if (file)
    {
        file->close();
        delete file;
        file = 0;
    }
}

QString FileUtils::getDir(const QString &fileName)
{
    QString dir = "";

    if (!fileName.isEmpty())
    {
        int index = fileName.lastIndexOf('/');
        if (index > 0)
        {
            dir = fileName.left(index);
        }
    }

    return dir;
}
