#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QCoreApplication>
#include "recordrunlog.h"

int my_vscprintf (const char * format, va_list pargs)
{
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}


QString strFormat(const QString &format, ...)
{
    std::string var_str;

    va_list	ap;
    va_start(ap, format);
    int len = my_vscprintf(format.toStdString().c_str(), ap);
    if (len > 0)
    {
        std::vector<char> buf(len + 1);
        vsprintf(&buf.front(), format.toStdString().c_str(), ap);
        var_str.assign(buf.begin(), buf.end() - 1);
    }
    va_end(ap);

    return QString::fromStdString(var_str);
}

void writeLog(const QString &tag, const QString &details, const char *fileName, const char *funcName, int line, App_RunLoG::AppenderType appenderType)
{
    QString timeInfo = " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") + "] ";
    QString fileInfo = QFileInfo(fileName).fileName() +":"+ QString::number(line) + "(" +funcName + ") ";
    QString msg = tag + timeInfo + fileInfo + details;
    AppRunLog::instance()->messageOutput(msg, "", AG::Debug, appenderType);
}

void operLog(const QString &details, const char *fileName, const char *funcName, int line)
{
    writeLog("[OPERLOG]", details, fileName, funcName, line, AG::File);
}

void execLog(const QString &details, const char *fileName, const char *funcName, int line)
{
    writeLog("[EXECLOG]", details, fileName, funcName, line, AG::File);
}

void errorLog(const QString &details, const char* fileName, const char *funcName, int line)
{
    writeLog("[ERROR]", details, fileName, funcName, line);
}

void infoLog(const QString &details, const char* fileName, const char *funcName, int line)
{
    writeLog("[INFO]", details, fileName, funcName, line);
}

void debugLog(const QString &details, const char *fileName, const char *funcName, int line)
{
#ifdef QT_NO_DEBUG
    // release dont not write log
#else
    writeLog("[DEBUG]", details, fileName, funcName, line, AG::Console);
#endif
}

AppRunLog *AppRunLog::instance()
{
    static QMutex mutex;
    static QScopedPointer<AppRunLog> inst;
    if (Q_UNLIKELY(!inst)) {
        mutex.lock();
        if (!inst) {
            inst.reset(new AppRunLog);
        }
        mutex.unlock();
    }

    return inst.data();
}

void AppRunLog::messageOutput(const QString &msgContent, const QString &msgModuleName, App_RunLoG::MessageLevel level, App_RunLoG::AppenderType appenderType)
{
    QMutexLocker locker(&m_mutex);

    if (!msgContent.isEmpty() && level >= m_messageLevel)
    {
        AG::RunLogData runlogData;
        runlogData.msgRecordTime = QDateTime::currentDateTime().toString("[yy-MM-dd/hh:mm:ss]");
        runlogData.msgContent = msgContent;
        runlogData.msgModuleName = msgModuleName;
        runlogData.msgAppender = appenderType;
        runlogData.level = level;

        //  数据入队
        m_msgDataQueue.enqueue(runlogData);

        if (!isRunning())
            start(LowPriority);
        else
            m_condition.wakeOne();
    }
}

void AppRunLog::run()
{
    while (!m_quit)
    {
        m_mutex.lock();
        bool isEmpty = m_msgDataQueue.isEmpty();
        AG::RunLogData runlogData;
        if (!isEmpty)
            runlogData = m_msgDataQueue.dequeue();
        m_mutex.unlock();

        if (!isEmpty)
            handleMsgData(runlogData);

        m_mutex.lock();
        if (m_msgDataQueue.empty() && !m_quit)
            m_condition.wait(&m_mutex);
        m_mutex.unlock();
    }
}

void AppRunLog::handleMsgData(const App_RunLoG::RunLogData &runlogData)
{
    switch (runlogData.msgAppender) {
    case AG::None:
        break;
    case AG::Console:
        outputMsgToConsole(runlogData);
        break;
    case AG::File:
        outPutMsgToFile(runlogData);
        break;
    case AG::AllOutput:
        outputMsgToConsole(runlogData);
        outPutMsgToFile(runlogData);
        break;
    default:
        break;
    }
}

void AppRunLog::outputMsgToConsole(const App_RunLoG::RunLogData &runLogData)
{
    //QString strLevel = levelInfo(runLogData.level);

#if !defined(QT_NO_DEBUG)
    //QString outPutMsg = runLogData.msgRecordTime + " " + QString("[%1]").arg(strLevel) + " " + runLogData.msgContent;
    //qDebug() << outPutMsg;
    qDebug() << runLogData.msgContent;
#else
    Q_UNUSED(runLogData);
#endif
}

void AppRunLog::outPutMsgToFile(const App_RunLoG::RunLogData &runLogData)
{
    //QString strLevel = levelInfo(runLogData.level);
    QString moduleName = runLogData.msgModuleName.isEmpty() ? "root" : runLogData.msgModuleName;
    QFile *file = recordFile(moduleName);
    if (file)
    {
        if (file->isOpen())
        {
            QTextStream logStream(file);
            //logStream << (runLogData.msgRecordTime + " " + QString("[%1]").arg(strLevel) + " " + runLogData.msgContent + "\n");
            logStream << (runLogData.msgContent + "\n");
        }
    }
}

QFile *AppRunLog::recordFile(const QString &msgModuleName)
{
    QFile *file = NULL;
    bool isNewDayFile = false;
    QDate currentDate = QDate::currentDate();
    QString strFileName = fileName(msgModuleName, currentDate, isNewDayFile);

    // 每天建立新文件之前，先检查删除SAVE_LOG_TIME时间之前记录的文件
    if (isNewDayFile)
    {
        removeOldfile(msgModuleName);
    }

    if (m_moduleFileHash.contains(msgModuleName))
    {
        file = m_moduleFileHash[msgModuleName];
        if (file)
        {
            if (file->fileName() != strFileName)
            {
                //qDebug() << "close file:" << file->fileName();
                file->close();
                delete file;
                file = NULL;
                m_moduleFileHash.remove(msgModuleName);
            }
        }
    }

    if (!file)
    {
        file = new QFile(strFileName);
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        {
            qCritical("create log file failed!");
            if (file)
            {
                delete file;
                file = NULL;
                return file;
            }
        }

        m_moduleFileHash[msgModuleName] = file;
    }

    return file;
}

QString AppRunLog::fileName(const QString &moduleName, const QDate &currentDate, bool &isNewDayFile)
{
    QString strCurrentDate = currentDate.toString("yyyy.MM.dd");
    QString fileName = m_logDirPath + "/";
    QString partName = moduleName + "-" + strCurrentDate + QString("-log");
    fileName += partName;

    if (QFile::exists(fileName))
    {
        int lastFileIndex = 0;
        if (!m_moduleFileIndexHash.contains(moduleName))
        {
            QDir dir(m_logDirPath);
            QStringList fileNameList = dir.entryList(QStringList(QString("%1_*").arg(partName)));
            foreach (QString strFileName, fileNameList) {
                QStringList nameInfo = strFileName.split("_");
                if (nameInfo.count() == 2)
                {
                    int fileIndex = QString(nameInfo.at(1)).toInt();
                    if (lastFileIndex <= fileIndex)
                    {
                        lastFileIndex = fileIndex;
                    }
                }
            }
            m_moduleFileIndexHash[moduleName] = lastFileIndex;
        }
        else
        {
            lastFileIndex = m_moduleFileIndexHash[moduleName];
        }

        QString lastModifiedFile = QString();
        if (lastFileIndex)
        {
            lastModifiedFile = partName + "_" + QString::number(lastFileIndex);
        }
        else
        {
            lastModifiedFile = partName;
        }

        QString fileFullPath = m_logDirPath + "/" + lastModifiedFile;
        QFileInfo fileInfo(fileFullPath);
        if (fileInfo.size() >= PERFILE_SIZE)
        {
            fileName += "_" + QString::number(lastFileIndex+1);
            m_moduleFileIndexHash[moduleName] = lastFileIndex+1;
            //qDebug() << "new file:" << fileName;
        }
        else
        {
            fileName = fileFullPath;
        }
        //qDebug() << "create file Name :" << fileName;
    }
    else
    {
        m_moduleFileIndexHash[moduleName] = 0;
        isNewDayFile = true;
    }

    return fileName;
}

void AppRunLog::removeOldfile(const QString &moduleName)
{
    QDateTime fileNameDate = QDateTime::fromSecsSinceEpoch(QDateTime::currentSecsSinceEpoch() - SAVE_LOG_TIME);
    QString strCurrentDate = fileNameDate.toString("yyyy.MM.dd");
    QString fileName = m_logDirPath + "/";
    QString partName = moduleName + "-" + strCurrentDate + QString("-log");
    fileName += partName;

    if (QFile::exists(fileName))
    {
        QFile::remove(fileName);
        QDir dir(m_logDirPath);
        QStringList fileNameList = dir.entryList(QStringList(QString("%1_*").arg(partName)));
        foreach (QString strFileName, fileNameList)
        {
            QString fileFullPath = m_logDirPath + "/" + strFileName;
            if (QFile::exists(fileFullPath))
            {
                QFile::remove(fileFullPath);
            }
        }
    }
}

QString AppRunLog::levelInfo(App_RunLoG::MessageLevel messageLevel)
{
    QString strLevel = QString();
    switch (messageLevel) {
    case AG::Debug:
        strLevel = "DEBUG";
        break;
    case AG::Info:
        strLevel = "INFO";
        break;
    case AG::Warning:
        strLevel = "WARNING";
        break;
    case AG::Critical:
        strLevel = "CRITICAL";
        break;
    case AG::Fatal:
        strLevel = "FATAL";
        break;
    default:
        break;
    }

    return strLevel;
}

AppRunLog::AppRunLog()
{
    m_quit = false;
    m_messageLevel = AG::Debug;

    // create directory "runlog".格式:应用名称-runlog
    m_logDirPath = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + "-runlog";

    QDir dir(m_logDirPath);
    if (!dir.exists())
    {
        dir.mkpath(m_logDirPath);
    }
}

AppRunLog::~AppRunLog()
{
    m_mutex.lock();
    foreach (QFile *file, m_moduleFileHash.values()) {
        if (file)
        {
            file->close();
            delete file;
            file = NULL;
        }
    }
    m_msgDataQueue.clear();
    m_moduleFileHash.clear();
    m_quit = true;
    m_condition.wakeOne();
    m_mutex.unlock();

    wait();
}
