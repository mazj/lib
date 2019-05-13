#ifndef DEFINE_DEBUG_H
#define DEFINE_DEBUG_H

#include <qglobal.h>
#include <QTime>

//#define NODEBUG

#if !defined(NODEBUG) && !defined(QT_NO_DEBUG)
#  define ENABLE_DEBUG_LOG
#endif

#ifdef ENABLE_DEBUG_LOG

#define APP_DEBUG \
    (qDebug().nospace() << QTime::currentTime().toString("hh:mm:ss:zzz") << " Loc: [" __FILE__ << "(" << __LINE__ << ")]:").space()

#else

#define APP_DEBUG \
    QMessageLogger().noDebug()

#endif // ENABLE_DEBUG_LOG

#endif // DEFINE_DEBUG_H
