#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>

#include "apputils.h"


bool AppUtils::isLandscape()
{
    //获取设备屏幕大小
    //QRect screenRect = QApplication::desktop()->screenGeometry();
//    qDebug() << "screen rect" << screenRect;

    //return screenRect.width() > screenRect.height();
    // 同一横屏处理
    return true;
}
