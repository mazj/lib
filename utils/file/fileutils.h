#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <QString>
#include <QFile>

const int FILE_TYPE_XML     = 1000;
const int FILE_TYPE_TXT     = FILE_TYPE_XML + 1;
const int FILE_TYPE_INI     = FILE_TYPE_XML + 2;
const int FILE_TYPE_EXCEL   = FILE_TYPE_XML + 3;

class FileUtils
{
public:
    static QString getFilePath(const QString &title, const QString &type, bool isOpen);
    static QString getOpenFilePath(const QString &title, const QString &type);
    static QString getSaveFilePath(const QString &title, const QString &type);
    static QString getSaveXmlFilePath(const QString &title);
    static QString getSaveWordFilePath(const QString &title);
    static QString getOpenExcelFilePath(const QString &title);
    static QString getOpenIniFilePath(const QString &title);
    static QString getOpenXmlFilePath(const QString &title);
    static QString getOpenTxtFilePath(const QString &title);
    static QString getOpenFilePath(const QString &title, int type);
    static QFile *fileOpen(const QString &path, bool isRead=true);
    static QFile *fileOpen(const QString &title, const QString &type, bool isRead);
    static QFile *fileRead(const QString &title, const QString &type);
    static QFile *fileWrite(const QString &title, const QString &type);
    static QFile *fileTxtRead(const QString &title);
    static QFile *fileXmlRead(const QString &title);
    static bool writeTxtFile(const QString &fileName, const QString &fileInfo);
    static void fileClose(QFile *file);

private:
    static QString getDir(const QString &fileName);


private:
    static QString s_lastDir;
};

#endif // FILE_UTILS_H
