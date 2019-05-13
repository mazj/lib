#ifndef APP_RUNLOG_CONSTANT_H
#define APP_RUNLOG_CONSTANT_H

#include <QString>

namespace App_RunLoG {

enum AppenderType
{
    None        = 0,
    File        = 1,
    Console     = 2,    // 打印终端
    AllOutput   = 3,  // 文件, 打印终端
};

// 输出信息等级
enum MessageLevel
{
    NoneLevel   = 0,
    Debug       = 1,
    Info        = 2,
    Warning     = 3,
    Critical    = 4,
    Fatal       = 5,
};

// 供给内部使用
typedef struct sRunLogData
{
    QString msgRecordTime;
    QString msgContent;
    QString msgModuleName; // 模块名称
    AppenderType msgAppender;
    MessageLevel level;

}RunLogData;


} // namespace App_RunLoG

#endif // APP_RUNLOG_CONSTANT_H
