#ifndef APP_RUN_LOG_H
#define APP_RUN_LOG_H

#include <QFile>
#include <QHash>
#include <QMutex>
#include <QQueue>
#include <QThread>
#include <QWaitCondition>
#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

#include "apprunlogconstant.h"

namespace AG = App_RunLoG;

QString strFormat(const QString &format, ...);

/*!
 * \brief writeLog 写日志
 * \param tag
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void writeLog(const QString &tag, const QString &details, const char* fileName,
              const char *funcName, int line, AG::AppenderType appenderType = AG::AllOutput);

/*!
 * \brief operLog 记录用户操作日志，只写文件
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void operLog(const QString &details, const char* fileName, const char *funcName, int line);

/*!
 * \brief execLog 程序自己的执行流程日志，只写文件
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void execLog(const QString &details, const char* fileName, const char *funcName, int line);

/*!
 * \brief errorLog 错误日志，写终端和文件
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void errorLog(const QString &details, const char* fileName, const char *funcName, int line);

/*!
 * \brief infoLog info信息，写终端和文件
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void infoLog(const QString &details, const char* fileName, const char *funcName, int line);

/*!
 * \brief debugLog debug信息，只往终端写, 只有debug模式下有用
 * \param details
 * \param fileName
 * \param funcName
 * \param line
 */
void debugLog(const QString &details, const char* fileName, const char *funcName, int line);



// 定义单个文件大小, test 1M
#define PERFILE_SIZE (1024*1024)

// 一个月
#define SAVE_LOG_TIME (30 * 24 * 3600)

//#define SAVE_LOG_TIME (1 * 24 * 3600)

#define AppDebug(...) \
    AppRunLog::instance()->messageOutput(__VA_ARGS__);

#define INFO(x) do { \
    QString timeInfo = " [" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") + "] "; \
    QString fileInfo = QFileInfo(__FILE__).fileName() +":"+ QString::number(__LINE__) + "(" + __func__ + ") "; \
    QString details = QString(x); \
    QString msg = "[INFO]" + timeInfo + fileInfo + details; \
    AppRunLog::instance()->messageOutput(msg); \
    } while(0)

#define OPERLOG(format, arg...) operLog(strFormat(format, ##arg), __FILE__,  __func__, __LINE__);
#define EXECLOG(format, arg...) execLog(strFormat(format, ##arg), __FILE__,  __func__, __LINE__);
#define ERRORLOG(format, arg...) errorLog(strFormat(format, ##arg), __FILE__,  __func__, __LINE__);
#define DEBUGLOG(format, arg...) debugLog(strFormat(format, ##arg), __FILE__,  __func__, __LINE__);
#define INFOLOG(format, arg...) infoLog(strFormat(format, ##arg), __FILE__,  __func__, __LINE__);

class AppRunLog : public QThread
{
public:
    ~AppRunLog();
    static AppRunLog *instance();

    /*!
     * \brief messageOutput 日志输出
     * \param msgContent    信息内容
     * \param msgModuleName 模块名称，默认为空（root），若模块不填该参数，则为plugin
     * \param level         信息输出等级
     * \param appenderType  输出载体，支持打印终端，记录文件
     */
    void messageOutput(const QString &msgContent, const QString &msgModuleName = "",
                       AG::MessageLevel level = AG::Debug,
                       AG::AppenderType appenderType = AG::AllOutput);

protected:
    void run() override;

private:
    void handleMsgData(const AG::RunLogData &runlogData);
    void outputMsgToConsole(const AG::RunLogData &runLogData);
    void outPutMsgToFile(const AG::RunLogData &runLogData);
    QFile *recordFile(const QString &msgModuleName);
    QString fileName(const QString &moduleName, const QDate &currentDate, bool &isNewDayFile);

    void removeOldfile(const QString &moduleName);
    QString levelInfo(AG::MessageLevel messageLevel);

private:
    AppRunLog();

private:
    QMutex m_mutex;
    QWaitCondition m_condition;
    bool m_quit;
    AG::MessageLevel m_messageLevel;

    QString m_logDirPath;
    // 日志数据缓冲区
    QQueue<App_RunLoG::RunLogData> m_msgDataQueue;
    QHash<QString, QFile *> m_moduleFileHash;
    // module Name, file index
    QHash<QString, int> m_moduleFileIndexHash;
};

#endif // APP_RUN_LOG_H
