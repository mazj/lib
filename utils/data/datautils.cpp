#include <QtGlobal>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTextCodec>

#include "datautils.h"
#include "protocoldatadefinition.h"
#include "i_pub_macro_def.h"
#include "runlog/recordrunlog.h"
//#include "excellcsnameidreader.h"
//#include "sysconfdata.h"
#include "consttestruns.h"
//#include "sglobjdatamanage.h"

using namespace ProtocolDataDef_NS;


QString DataUtils::gbk2Utf8(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    //gbk -> utf8
    //1. gbk to unicode
    QString strUnicode = gbk->toUnicode(inStr.toLocal8Bit().data());
    //2. unicode -> utf-8
    QByteArray utf8_bytes = utf8->fromUnicode(strUnicode);
    return utf8_bytes.data(); //获取其char *
}

QString DataUtils::utf82Gbk(const QString &inStr)
{
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    //utf8 -> gbk
    //1. utf8 -> unicode
    QString strUnicode = utf8->toUnicode(inStr.toLocal8Bit().data());
    //2. unicode -> gbk, 得到QByteArray
    QByteArray gb_bytes = gbk->fromUnicode(strUnicode);

    return gb_bytes.data(); //获取其char *
}

QString DataUtils::pChar2HexString(const char *src, int len)
{
    return QString(QByteArray(src, len).toHex());
}

QString DataUtils::num2HexString(int num)
{
    return QString().number(num, 16).prepend("0x");
}

void DataUtils::stringCopy(STRING dst, const QString &src)
{
    // 先清空
    memset(dst, 0, sizeof(STRING));

    std::string tmp = src.toStdString();
    const char *data = tmp.c_str();
    quint32 size = (strlen(data) > sizeof(STRING)) ? sizeof(STRING) : strlen(data);

    // 后赋值
    memcpy(dst, data, size);
}

quint8 DataUtils::getCbiRouteSigShowDef(const QString &show, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (show.isEmpty())
    {
        return result;
    }

    if (STR_CBI_ROUTE_SIG_LIGHT_OFF == show)
        result = CBI_ROUTE_SIG_LIGHT_OFF;
    else if (STR_CBI_ROUTE_SIG_LIGHT_H == show)
        result = CBI_ROUTE_SIG_LIGHT_H;
    else if (STR_CBI_ROUTE_SIG_LIGHT_UU == show)
        result = CBI_ROUTE_SIG_LIGHT_UU;
    else if (STR_CBI_ROUTE_SIG_LIGHT_USU == show)
        result = CBI_ROUTE_SIG_LIGHT_USU;
    else if (STR_CBI_ROUTE_SIG_LIGHT_U == show)
        result = CBI_ROUTE_SIG_LIGHT_U;
    else if (STR_CBI_ROUTE_SIG_LIGHT_LU == show)
        result = CBI_ROUTE_SIG_LIGHT_LU  ;
    else if (STR_CBI_ROUTE_SIG_LIGHT_L == show)
        result = CBI_ROUTE_SIG_LIGHT_L;
    else if (STR_CBI_ROUTE_SIG_LIGHT_HB == show)
        result = CBI_ROUTE_SIG_LIGHT_HB;
    else if (STR_CBI_ROUTE_SIG_LIGHT_B == show)
        result = CBI_ROUTE_SIG_LIGHT_B;
    else if (STR_CBI_ROUTE_SIG_LIGHT_A == show)
        result = CBI_ROUTE_SIG_LIGHT_A;
    else if (STR_CBI_ROUTE_SIG_LIGHT_HDERR == show)
        result = CBI_ROUTE_SIG_LIGHT_H;
    else
    {
        flag = false;
        ERRORLOG("failed show:"+show);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiSignalOutStatusDef(const QString &show, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (show.isEmpty())
    {
        return result;
    }

    if (STR_CBI_SIG_OUT_LIGHT_OFF == show)
    {
        result = CBI_SIG_OUT_LIGHT_OFF;
    }
    else if (STR_CBI_SIG_OUT_LIGHT_ON == show)
    {
        result = CBI_SIG_OUT_LIGHT_ON;
    }
    else
    {
        flag = false;
        ERRORLOG("failed show:"+show);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiJZSglShiftSta(const QString &show, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (show.isEmpty())
    {
        return result;
    }

    if (STR_CBI_ROUTE_SIG_LIGHT_HDERR == show || STR_CBI_ROUTE_SIG_LIGHT_HDERR_2 == show)
    {
        result = CBI_SIG_LIGHT_ERR;
    }
    else if (STR_CBI_ROUTE_SIG_LIGHT_NORMAL == show)
    {
        result = CBI_SIG_LIGHT_NORMAL;
    }
    else
    {
        flag = false;
        ERRORLOG("failed show:"+show);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiSglShutSta(const QString &show, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (show.isEmpty())
    {
        return result;
    }

    if (STR_CBI_SGL_SHUT_FLAG_OPEN == show)
    {
        result = CBI_SGL_SHUT_FLAG_OPEN;
    }
    else if (STR_CBI_SGL_SHUT_FLAG_CLOSE == show)
    {
        result = CBI_SGL_SHUT_FLAG_CLOSE;
    }
    else
    {
        flag = false;
        ERRORLOG("failed show:"+show);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

void DataUtils::initCbiSbStatusDef(UINT8 *cbiLockStatus)
{
    if (!cbiLockStatus)
    {
        return;
    }

    for (int i = 0; i < MAX_CBI_TO_TCC_ONE_RTE_SECT_NUM; i++)
    {
        *(cbiLockStatus+i) = CBI_QD_STATUS_SB;
    }
}

quint8 DataUtils::getCbiSbStatusDef(const QString &status, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (status.isEmpty())
    {
        return result;
    }

    if (STR_CBI_QD_STATUS_SB == status)
    {
        result = CBI_QD_STATUS_SB;
    }
    else if (STR_CBI_QD_STATUS_JS == status)
    {
        result = CBI_QD_STATUS_JS;
    }
    else
    {
        flag = false;
        ERRORLOG("failed status:"+status);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiFsjDef(const QString &value, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (value.isEmpty())
    {
        return result;
    }

    if (STR_CBI_CHG_DIR_SB == value || STR_CBI_CHG_DIR_LX == value)
    {
        result = CBI_CHG_DIR_FSJ_SB;
    }
    else if (STR_CBI_CHG_DIR_WSB == value || STR_CBI_CHG_DIR_XQ == value)
    {
        result = CBI_CHG_DIR_FSJ_WSB;
    }
    else
    {
        flag = false;
        ERRORLOG("failed, value:"+value);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiFqjDef(const QString &value, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (value.isEmpty())
    {
        return result;
    }

    if (STR_CBI_CHG_DIR_XQ == value || STR_CBI_CHG_DIR_FQJ_Y == value)
    {
        result = CBI_CHG_DIR_FQJ_XQ;
    }
    else if (STR_CBI_CHG_DIR_LX == value || STR_CBI_CHG_DIR_FQJ_N == value)
    {
        result = CBI_CHG_DIR_FQJ_LX;
    }
    else
    {
        flag = false;
        ERRORLOG("failed value:"+value);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiJfajDef(const QString &value, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (value.isEmpty())
    {
        return result;
    }

    if (STR_CBI_CHG_DIR_XQ == value || STR_CBI_CHG_DIR_JFAJ_Y == value)
    {
        result = CBI_CHG_DIR_JFAJ_XQ;
    }
    else if (STR_CBI_CHG_DIR_LX == value || STR_CBI_CHG_DIR_JFAJ_N == value)
    {
        result = CBI_CHG_DIR_JFAJ_LX;
    }
    else
    {
        flag = false;
        ERRORLOG("failed value:"+value);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getCbiFfajDef(const QString &value, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (value.isEmpty())
    {
        return result;
    }

    if (STR_CBI_CHG_DIR_XQ == value || STR_CBI_CHG_DIR_FFAJ_Y == value)
    {
        result = CBI_CHG_DIR_FFAJ_XQ;
    }
    else if (STR_CBI_CHG_DIR_LX == value || STR_CBI_CHG_DIR_FFAJ_N == value)
    {
        result = CBI_CHG_DIR_FFAJ_LX;
    }
    else
    {
        flag = false;
        ERRORLOG("failed value:"+value);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccCodeOrderDef(const QString &order, bool *ok)
{
    bool flag = true;
    quint8 result = 0;
    if (order.isEmpty())
    {
        return result;
    }

    if (STR_TCC_CODE_ORDER_H == order)
        result = TCC_CODE_ORDER_H;
    else if (STR_TCC_CODE_ORDER_HU == order)
        result = TCC_CODE_ORDER_HU;
    else if (STR_TCC_CODE_ORDER_HB == order)
        result = TCC_CODE_ORDER_HB;
    else if (STR_TCC_CODE_ORDER_L6 == order)
        result = TCC_CODE_ORDER_L6;
    else if (STR_TCC_CODE_ORDER_U2S == order)
        result = TCC_CODE_ORDER_U2S;
    else if (STR_TCC_CODE_ORDER_UU == order)
        result = TCC_CODE_ORDER_UU;
    else if (STR_TCC_CODE_ORDER_LU2 == order)
        result = TCC_CODE_ORDER_LU2;
    else if (STR_TCC_CODE_ORDER_LU == order)
        result = TCC_CODE_ORDER_LU;
    else if (STR_TCC_CODE_ORDER_L == order)
        result = TCC_CODE_ORDER_L;
    else if (STR_TCC_CODE_ORDER_ZJ == order)
        result = TCC_CODE_ORDER_ZJ;
    else if (STR_TCC_CODE_ORDER_QP == order)
        result = TCC_CODE_ORDER_QP;
    else if (STR_TCC_CODE_ORDER_L4 == order)
        result = TCC_CODE_ORDER_L4;
    else if (STR_TCC_CODE_ORDER_L5 == order)
        result = TCC_CODE_ORDER_L5;
    else if (STR_TCC_CODE_ORDER_UUS == order)
        result = TCC_CODE_ORDER_UUS;
    else if (STR_TCC_CODE_ORDER_U == order)
        result = TCC_CODE_ORDER_U;
    else if (STR_TCC_CODE_ORDER_U2 == order)
        result = TCC_CODE_ORDER_U2;
    else if (STR_TCC_CODE_ORDER_L2 == order)
        result = TCC_CODE_ORDER_L2;
    else if (STR_TCC_CODE_ORDER_L3 == order)
        result = TCC_CODE_ORDER_L3;
    else
    {
        flag = false;
        ERRORLOG("failed, order:"+order);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccLfDef(const QString &lf, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (lf.isEmpty())
    {
        return result;
    }

    if (lf.contains(STR_TCC_CURRENT_LF))
    {
        result = TCC_CURRENT_LF;
    }
    else if (lf.contains(STR_TCC_BILLBOARD_LF))
    {
        result = TCC_BILLBOARD_LF;
    }
    else
    {
        flag = false;
        ERRORLOG("failed, lf:"+lf);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccQdZyStatusDef(const QString &qdZy, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (qdZy.isEmpty())
    {
        return result;
    }

    if (STR_TCC_BOUND_ZY == qdZy)
        result = TCC_BOUND_ZY;
    else if (STR_TCC_BOUND_ZY_ERR == qdZy)
        result = TCC_BOUND_ZY_ERR;
    else if (STR_TCC_BOUND_FREE == qdZy)
        result = TCC_BOUND_FREE;
    else if (STR_TCC_BOUND_FLBL == qdZy)
        result = TCC_BOUND_FLBL;
    else
    {
        flag = false;
        ERRORLOG("failed, qdzy:"+qdZy);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccSigBreakDef(const QString &status, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (status.isEmpty())
    {
        return result;
    }

    if (STR_TCC_SIG_BREAK == status)
    {
        result = TCC_SIG_BREAK;
    }
    else if (STR_TCC_SIG_NORMAL == status)
    {
        result = TCC_SIG_NORMAL;
    }
    else if (STR_TCC_SIG_UNCONF == status)
    {
        result = TCC_SIG_UNCONF;
    }
    else
    {
        flag = false;
        ERRORLOG("failed, status:"+status);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccTsrCoverFlagDef(const QString &coverFlag, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (coverFlag.isEmpty())
    {
        return result;
    }

    if ("反向覆盖" == coverFlag)
    {
        result = COVER_FLAG_FX;
    }
    else if ("正向覆盖" == coverFlag)
    {
        result = COVER_FLAG_ZX;
    }
    else if ("本地" == coverFlag)
    {
        result = COVER_FLAG_BD;
    }
    else
    {
        flag = false;
        ERRORLOG("failed flag:"+coverFlag);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getTccChgDirDef(const QString &value, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (value.isEmpty())
    {
        return result;
    }

    if (STR_TCC_ZONE_FSJ_LX == value)
        result = TCC_ZONE_FSJ_LX;
    else if (STR_TCC_ZONE_FSJ_XQ == value || STR_TCC_DE_PORT_DIR_F_N == value)
        result = TCC_ZONE_FSJ_XQ;
    else if (STR_TCC_ZONE_ROUTE_FLAG_Y == value || STR_TCC_ZONE_ROUTE_FLAG_Y_2 == value)
        result = TCC_ZONE_ROUTE_FLAG_Y;
    else if (STR_TCC_ZONE_ROUTE_FLAG_N == value || STR_TCC_ZONE_ROUTE_FLAG_N_2 == value)
        result = TCC_ZONE_ROUTE_FLAG_N;
    else if (STR_TCC_ZONE_STATUS_ZY == value)
        result = TCC_ZONE_STATUS_ZY;
    else if (STR_TCC_ZONE_STATUS_FREE == value)
        result = TCC_ZONE_STATUS_FREE;
    else if (STR_TCC_ZONE_CHG_DIR_TYPE_NORMAL == value)
        result = TCC_ZONE_CHG_DIR_TYPE_NORMAL;
    else if (STR_TCC_ZONE_CHG_DIR_TYPE_ASSIST == value)
        result = TCC_ZONE_CHG_DIR_TYPE_ASSIST;
    else if (STR_TCC_ZONE_CHG_DIR_TYPE_NONE== value)
        result = TCC_ZONE_CHG_DIR_TYPE_NONE;
    else if (STR_TCC_ZONE_CHG_DIR_RESULT_Q == value || STR_TCC_ZONE_CHG_DIR_RESULT_Q_2 == value)
        result = TCC_ZONE_CHG_DIR_RESULT_Q;
    else if (STR_TCC_ZONE_CHG_DIR_RESULT_Y == value || STR_TCC_ZONE_CHG_DIR_RESULT_Y_2 == value)
        result = TCC_ZONE_CHG_DIR_RESULT_Y;
    else if (STR_TCC_ZONE_CHG_DIR_RESULT_N == value)
        result = TCC_ZONE_CHG_DIR_RESULT_N;
    else if (STR_TCC_DE_PORT_DIR_J == value)
        result = TCC_DE_PORT_DIR_J;
    else if (STR_TCC_DE_PORT_DIR_F == value)
        result = TCC_DE_PORT_DIR_F;
    else if (STR_TCC_DE_PORT_DIR_W == value)
        result = TCC_DE_PORT_DIR_W;
    else
    {
        flag = false;
        ERRORLOG("failed value:"+value);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getLcsZyStatusDef(const QString &status, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if (status.isEmpty())
    {
        return result;
    }

    if (status.contains(STR_LCS_QD_STATUS_FREE))
    {
        result = LCS_QD_STATUS_FREE;
    }
    else if (status.contains(STR_LCS_QD_STATUS_ZY))
    {
        result = LCS_QD_STATUS_ZY;
    }
    else
    {
        flag = false;
        ERRORLOG("failed status:"+status);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

void DataUtils::copyLcsBaliseMsg(char dst[], const QString &src)
{
    // 将src每两个字节转换成一个16进制，如果src是奇数，则结尾补F
    QString hexStr = (src.size()&1) ? src + "F" : src;
    QByteArray bytes = QByteArray::fromHex(hexStr.toLatin1());
    int size = bytes.size() < 128 ? bytes.size() : 128;
    memcpy(dst, bytes.data(), size);
}

quint8 DataUtils::getLcsRelayStatusDef(const QString &status, bool *ok)
{
    bool flag = true;
    quint8 result = 0;


    if (STR_LCS_RELAY_STATUS_NORMAL == status)
    {
        result = LCS_RELAY_STATUS_NORMAL;
    }
    else if (STR_LCS_RELAY_STATUS_UP == status)
    {
        result = LCS_RELAY_STATUS_UP;
    }
    else if (STR_LCS_RELAY_STATUS_DOWN == status)
    {
        result = LCS_RELAY_STATUS_DOWN;
    }
    else if (STR_LCS_RELAY_STATUS_UNKOWN == status)
    {
        result = LCS_RELAY_STATUS_UNKOWN;
    }
    else
    {
        flag = false;
        ERRORLOG("failed, " + status);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

quint8 DataUtils::getLcsTsrsStatusDef(const QString &status, bool *ok)
{
    bool flag = true;
    quint8 result = 0;

    if ("设置" == status)
    {
        result = 0xAA;
    }
    else if ("取消" == status)
    {
        result = 0x55;
    }
    else
    {
        flag = false;
        ERRORLOG("failed, " + status);
    }

    if (ok)
    {
        *ok = flag;
    }

    return result;
}

QString DataUtils::getFileName(const QString &path)
{
    // 取之后一个/之后的内容
    int index = path.lastIndexOf("/");
    if (index < 0)
    {
        return path;
    }

    QString fileName = path.right(path.length()-index-1);
    // 去掉文件类型后缀
    index = fileName.lastIndexOf(".");
    if (index < 0)
    {
        return fileName;
    }

    return fileName.left(index);
}

QString DataUtils::getLcsLfName(const quint8 lf)
{
    QString r = "";

    switch (lf) {
    case 0x03:
        r = "H";
        break;
    case 0x09:
        r = "HU";
        break;
    case 0x21:
        r = "HB";
        break;
    case 0x0a:
        r = "L6";
        break;
    case 0x22:
        r = "U2S";
        break;
    case 0x14:
        r = "UU";
        break;
    case 0x18:
        r = "LU2";
        break;
    case 0x30:
        r = "LU";
        break;
    case 0x3a:
        r = "L";
        break;
    case 0x05:
        r = "占用检查";
        break;
    case 0x11:
        r = "载频切换";
        break;
    case 0x06:
        r = "L4";
        break;
    case 0x12:
        r = "L5";
        break;
    case 0x0c:
        r = "UUS";
        break;
    case 0x24:
        r = "U";
        break;
    case 0x28:
        r = "U2";
        break;
    case 0x3c:
        r = "L2";
        break;
    case 0x36:
        r = "L3";
        break;
    default:
        break;
    }

    return r;
}

QString DataUtils::getLcsCfName(const quint8 cf)
{
    QString r = "";

    switch (cf) {
    case 1:
        r = "1700-1";
        break;
    case 2:
        r = "1700-2";
        break;
    case 4:
        r = "2000-1";
        break;
    case 8:
        r = "2000-2";
        break;
    case 7:
        r = "2300-1";
        break;
    case 11:
        r = "2300-2";
        break;
    case 13:
        r = "2600-1";
        break;
    case 14:
        r = "2600-2";
        break;
    default:
        break;
    }
    return r;
}

QString DataUtils::getUsercaseType(const QString &usercaseName)
{
    if (usercaseName.contains(ConstTestRuns_NS::ABBR_NAME_CASE_ORDER))
    {
        return ConstTestRuns_NS::ABBR_NAME_CASE_ORDER;
    }

    if (usercaseName.contains(ConstTestRuns_NS::ABBR_NAME_BALISE_MSG))
    {
        return ConstTestRuns_NS::ABBR_NAME_BALISE_MSG;
    }

    if (usercaseName.contains(ConstTestRuns_NS::ABBR_NAME_ZONE_CHG_DIR))
    {
        return ConstTestRuns_NS::ABBR_NAME_ZONE_CHG_DIR;
    }

    return usercaseName;
}

QString DataUtils::getCbi2TccZoneDirStatus(quint8 status)
{
    QString strStatus;

    switch (status)
    {
    case RELAY_STATUS_UP:
        strStatus = "吸起";
        break;
    case RELAY_STATUS_DOWN:
        strStatus = "落下";
        break;
    case RELAY_STATUS_NONE:
        strStatus = "状态未知";
        break;
    default:
        break;
    }

    return strStatus;
}

QString DataUtils::getCbi2TccRouteInfoStatus(quint8 status)
{
    QString strStatus;

    switch (status)
    {
    case SGL_LIGHT_OFF:
        strStatus = "灭灯";
        break;
    case SGL_LIGHT_H:
        strStatus = "红灯";
        break;
    case SGL_LIGHT_UU:
        strStatus = "双黄灯";
        break;
    case SGL_LIGHT_UUS:
        strStatus = "双黄闪灯";
        break;
    case SGL_LIGHT_U:
        strStatus = "黄灯";
        break;
    case SGL_LIGHT_LU:
        strStatus = "绿黄灯";
        break;
    case SGL_LIGHT_L:
        strStatus = "绿灯";
        break;
    case SGL_LIGHT_HB:
        strStatus = "红白灯";
        break;
    case SGL_LIGHT_BAI:
        strStatus = "白灯";
        break;
    case SGL_LIGHT_LAN:
        strStatus = "兰灯";
        break;
    default:
        break;
    }

    return strStatus;
}

QString DataUtils::getCbi2TCCSiganlBrokenWire(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x55:
        strStatus = "信号机正常";
        break;
    case 0xAA:
        strStatus = "信号机断丝";
        break;
    case 0xFF:
        strStatus = "没有配置防护信号机";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getCbi2TCCLineState(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x11:
        strStatus = "信号机调车信号开放";
        break;
    case 0x22:
        strStatus = "调车信号关闭";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiYFJInfo(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0xAA:
        strStatus = "继电器吸起";
        break;
    case 0x55:
        strStatus = "继电器落下";
        break;
    case 0xFF:
        strStatus = "继电器状态未知";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiSectionStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0xAA:
        strStatus = "占用";
        break;
    case 0x55:
        strStatus = "空闲";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiFZBLStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x11:
        strStatus = "灭灯";
        break;
    case 0x22:
        strStatus = "闪灯";
        break;
    case 0x33:
        strStatus = "稳亮灯";
        break;
    case 0xFF:
        strStatus = "未知";
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiBLKStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x55:
        strStatus = "占用";
        break;
    case 0xAA:
        strStatus = "空闲";
        break;
    case 0x11:
        strStatus = "故障";
        break;
    case 0x22:
        strStatus = "失去分路";
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiSigTsrStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x11:
        strStatus = "不降级";
        break;
    case 0x22:
        strStatus = "降级";
        break;
    case 0x33:
        strStatus = "未知";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiRedSignalBrokenWire(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0x55:
        strStatus = "信号机正常";
        break;
    case 0xAA:
        strStatus = "信号机断丝";
        break;
    case 0xFF:
        strStatus = "没有配置防护信号机";
        break;
    default:
        break;
    }
    return strStatus;
}

QString DataUtils::getTccToCbiYWQXStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
    case 0xAA:
        strStatus = "无异物侵限";
        break;
    case 0x55:
        strStatus = "有异物侵限";
        break;
    case 0xFF:
        strStatus = "无配置";
        break;
    default:
        break;
    }
    return strStatus;
}

//#define ZH_STATUS_NO 0x55//无灾害
//#define ZH_STATUS_YES 0xAA//发生灾害
QString DataUtils::getTcc2TccBoundaryZHSta(quint8 status)
{
    QString strStatus;
    switch (status) {
    case ZH_STATUS_NO:
        strStatus = "无灾害";
        break;
    case ZH_STATUS_YES:
        strStatus = "发生灾害";
        break;
    default:
        break;
    }
    return strStatus;
}

quint8 DataUtils::getTcc2TccBoundaryZHSta(const QString &status)
{
    quint8 r = ZH_STATUS_NO;
    if ("发生灾害" == status)
    {
        r = ZH_STATUS_YES;
    }

    return r;
}

QString DataUtils::getTcc2TccBoundaryBlkSta(quint8 status)
{
    QString strStatus;
    switch(status)
    {
    case BLK_SEC_STATUS_KX:
        strStatus = "空闲";
        break;
    case BLK_SEC_STATUS_ZY:
         strStatus = "占用";
        break;
    case BLK_SEC_STATUS_GZ:
         strStatus = "故障";
        break;
    default:
         strStatus = "失去分路";
        break;
    }
    return strStatus;
}

//#define SGL_RED_BAD_NO 0x55//信号机正常
//#define SGL_RED_BAD_YES 0xAA//信号机断丝
//#define SGL_RED_BAD_NONE 0xFF//没有配置防护信号机
QString DataUtils::getTcc2TccSglHDErrSta(quint8 status)
{
    QString strStatus;
    switch(status)
    {
    case SGL_RED_BAD_NO:
        strStatus = "信号机正常";
        break;
    case SGL_RED_BAD_YES:
         strStatus = "信号机断丝";
        break;
    case SGL_RED_BAD_NONE:
         strStatus = "没有配置防护信号机";
        break;
    default:
         strStatus = "";
        break;
    }
    return strStatus;
}

QString DataUtils::getTcc2TccBlkLowFre(quint8 status)
{
    return getLcsLfName(status);
}
//#define LOW_FRE_MODE_HOME 0x11//本段低频
//#define LOW_FRE_MODE_PRE  0x22//预告低频
QString DataUtils::getTcc2TccLowFreMode(quint8 status)
{
    QString strStatus;
    switch (status) {
    case LOW_FRE_MODE_HOME:
        strStatus = "本段低频";
        break;
    case LOW_FRE_MODE_PRE:
        strStatus  = "预告低频";
        break;
    default:
           strStatus  = "";
        break;
    }
    return strStatus;
}

QString DataUtils::getTcc2TccBorderBlkStatus(quint8 status)
{
  QString strStatus;
  switch (status) {
    case 1:
      strStatus = "占用";
      break;
    case 2:
      strStatus = "空闲";
      break;
    case 0:
      strStatus = "故障占用";
      break;
    case 3:
      strStatus = "失去分路";
      break;
    default:
        strStatus = "";
      break;
    }
  return strStatus;
}

QString DataUtils::getTcc2TccSignalHDErrStatus(quint8 status)
{
  QString strStatus;
  switch (status) {
    case 0:
      strStatus = "断丝";
      break;
    case 1:
      strStatus = "无配置";
      break;
    case 3:
      strStatus = "正常";
      break;
    default:
        strStatus = "";
      break;
    }
  return strStatus;
}

quint8 DataUtils::getTccConnStatus(const QString &status)
{
    if ("无连接" == status)
    {
        return COMM_STATUS_NONE;
    }

    if ("正常" == status)
    {
        return COMM_STATUS_CONNECTED;
    }

    return COMM_STATUS_CONNECTING;
}

quint8 DataUtils::getTccWorkStatus(const QString &status)
{
    if (status.contains("单机"))
    {
        return SYS_WORK_STA_ONE;
    }

    if (status.contains("双机"))
    {
        return SYS_WORK_STA_TWO;
    }

    return SYS_WORK_STA_NONE;
}

quint8 DataUtils::getTccMainCtrlStatus(const QString &status)
{
    if ("A机主控" == status)
    {
        return MAIN_CTRL_SYSTEM_A;
    }

    if ("B机主控" == status)
    {
        return MAIN_CTRL_SYSTEM_B;
    }

    return MAIN_CTRL_SYSTEM_NONE;
}

quint8 DataUtils::getTccblkInitStatus(const QString &status)
{
    if ("初始化完成" == status)
    {
        return COMM_INIT_YES;
    }

    if ("未初始化" == status)
    {
        return COMM_INIT_NO;
    }

    return COMM_INIT_NONE;
}

quint8 DataUtils::getTccLeuStatus(const QString &status)
{
    if ("有效配置" == status)
    {
        return CONFIGURATION_VALID_YES;
    }

    return CONFIGURATION_VALID_NO;
}

quint8 DataUtils::getTccPermitStatus(const QString &status)
{
    if ("空闲" == status)
    {
        return SIGNAL_PERMIT_STATE_KX;
    }

    if ("正常占用" == status)
    {
        return SIGNAL_PERMIT_STATE_ZCZY;
    }

    if ("失去分路" == status)
    {
        return SIGNAL_PERMIT_STATE_SQFL;
    }

    return SIGNAL_PERMIT_STATE_GZZY;
}

quint8 DataUtils::getTccPermitFlowStatus(const QString &status)
{
    if ("无信号许可" == status)
    {
        return SIGNAL_PERMIT_FLOW_NONE;
    }

    if ("发起信号许可" == status)
    {
        return SIGNAL_PERMIT_FLOW_START;
    }

    if ("应答信号许可" == status)
    {
        return SIGNAL_PERMIT_FLOW_RESPONSE;
    }

    return SIGNAL_PERMIT_FLOW_GZ;
}

quint8 DataUtils::getTccZoneLogicCheckStatus(const QString &status)
{
    if ("启用" == status)
    {
        return ZONG_LOGIC_CHECK_START;
    }

    if ("关闭" == status)
    {
        return ZONG_LOGIC_CHECK_CLOSE;
    }

    return ZONG_LOGIC_CHECK_GZ;
}

//#define TRAIN_ZONE_STATUS_ZY 0x55//占用
//#define TRAIN_ZONE_STATUS_KX 0xAA//空闲
QString DataUtils::getTcc2TccZoneStatus(quint8 status)
{
    QString strStatus;
    switch (status) {
      case TRAIN_ZONE_STATUS_ZY:
        strStatus = "占用";
        break;
      case TRAIN_ZONE_STATUS_KX:
        strStatus = "空闲";
        break;
      default:
          strStatus = "";
        break;
      }
    return strStatus;
}
////线路进路
//#define SUB_LINE_ZONE_ROUTE_NO  0x55//无区间进路
//#define SUB_LINE_ZONE_ROUTE_YES 0xAA//有区间进路
QString DataUtils::getTcc2TccZoneRouteFlag(quint8 status)
{
  QString strStatus;
  switch (status) {
    case SUB_LINE_ZONE_ROUTE_NO:
      strStatus = "无区间进路";
      break;
    case SUB_LINE_ZONE_ROUTE_YES:
      strStatus = "有区间进路";
      break;
    default:
       strStatus = "";
      break;
    }
  return strStatus;
}

////线路发车锁闭状态
//#define SUB_LINE_FSJ_UP  0x55//FSJ吸起 无发车
//#define SUB_LINE_FSJ_DOWN 0xAA//FSJ落下 有发车进路
QString DataUtils::getTcc2TccZoneFSJStatus(quint8 status)
{
  QString strStatus;
  switch (status) {
    case SUB_LINE_FSJ_UP:
      strStatus = "FSJ吸起 无发车";
      break;
    case SUB_LINE_FSJ_DOWN:
      strStatus = "FSJ落下 有发车进路";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}
//运行方向
//#define RUN_DIR_NONE 0xff//未取向
//#define RUN_DIR_FC 0x55//发车
//#define RUN_DIR_JC 0xAA//接车

QString DataUtils::getTcc2Tccuc_DePortDir(quint8 status)
{
  QString strStatus;
  switch (status) {
    case RUN_DIR_NONE:
      strStatus = "未取向 ";
      break;
    case RUN_DIR_FC:
      strStatus = "发车";
      break;
    case RUN_DIR_JC:
      strStatus = "接车";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}
//改方类型
//#define SUB_LINE_CHG_DIR_TYPE_NORMAL 0x11//正常改方
//#define SUB_LINE_CHG_DIR_TYPE_ASSIST 0x22//辅助改方
//#define SUB_LINE_CHG_DIR_TYPE_NONE 0xff//无改方操作
QString DataUtils::getTcc2TccChgDirType(quint8 status)
{
  QString strStatus;
  switch (status) {
    case SUB_LINE_CHG_DIR_TYPE_NORMAL:
      strStatus = "正常改方 ";
      break;
    case SUB_LINE_CHG_DIR_TYPE_ASSIST:
      strStatus = "辅助改方";
      break;
    case SUB_LINE_CHG_DIR_TYPE_NONE:
      strStatus = "无改方操作";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}
//改方结果
//#define SUB_LINE_CHG_DIR_RES_REQ 0x11//请求改方
//#define SUB_LINE_CHG_DIR_RES_ALLOW 0x22//允许改方
//#define SUB_LINE_CHG_DIR_RES_NOALLOW 0x33//不允许改方
QString DataUtils::getTcc2TccChgDirResult(quint8 status)
{
  QString strStatus;
  switch (status) {
    case SUB_LINE_CHG_DIR_RES_REQ:
      strStatus = "请求改方 ";
      break;
    case SUB_LINE_CHG_DIR_RES_ALLOW:
      strStatus = "允许改方";
      break;
    case SUB_LINE_CHG_DIR_RES_NOALLOW:
      strStatus = "不允许改方";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

//信号机状态
QString DataUtils::getTcc2TccSignalStatus(quint8 status)
{
  QString strStatus;
  switch(status)
    {
    case SGL_LIGHT_OFF:
      strStatus = "灭灯";
      break;
    case SGL_LIGHT_H:
       strStatus = "红灯";
      break;
    case SGL_LIGHT_UU:
       strStatus = "双黄灯";
      break;
    case SGL_LIGHT_UUS:
       strStatus = "双黄闪灯";
      break;
    case SGL_LIGHT_U:
       strStatus = "黄灯";
      break;
    case SGL_LIGHT_LU:
       strStatus = "绿黄灯";
      break;
    case SGL_LIGHT_L:
        strStatus = "绿灯";
      break;
    case SGL_LIGHT_HB:
        strStatus = "红白灯";
      break;
    case SGL_LIGHT_BAI:
        strStatus = "白灯";
      break;
    case SGL_LIGHT_LAN:
        strStatus = "蓝灯";
      break;
    case SGL_LIGHT_LD_ERR:
      strStatus = "绿灯丝故障";
      break;
    default:
       strStatus = "";
      break;
    }
  return strStatus;
}

quint8 DataUtils::getTcc2TccSignalStatus(const QString &status)
{
    if (STR_CBI_ROUTE_SIG_LIGHT_OFF == status)
        return SGL_LIGHT_OFF;
    if (STR_CBI_ROUTE_SIG_LIGHT_H == status)
        return SGL_LIGHT_H;
    if (STR_CBI_ROUTE_SIG_LIGHT_UU == status)
        return SGL_LIGHT_UU;
    if (STR_CBI_ROUTE_SIG_LIGHT_USU == status || STR_CBI_ROUTE_SIG_LIGHT_USU_2 == status)
        return SGL_LIGHT_UUS;
    if (STR_CBI_ROUTE_SIG_LIGHT_U == status)
        return SGL_LIGHT_U;
    if (STR_CBI_ROUTE_SIG_LIGHT_LU == status)
        return SGL_LIGHT_LU;
    if (STR_CBI_ROUTE_SIG_LIGHT_L == status)
        return SGL_LIGHT_L;
    if (STR_CBI_ROUTE_SIG_LIGHT_HB == status)
        return SGL_LIGHT_HB;
    if (STR_CBI_ROUTE_SIG_LIGHT_B == status)
        return SGL_LIGHT_BAI;
    if (STR_CBI_ROUTE_SIG_LIGHT_A == status)
        return SGL_LIGHT_LAN;
    if (STR_CBI_ROUTE_SIG_LIGHT_HDERR == status || STR_CBI_ROUTE_SIG_LIGHT_HDERR_2 == status)
        return SGL_LIGHT_LD_ERR;

    return 0x0f;
}

QString DataUtils::getTcc2TccBlkSectStatus(quint8 status)
{
  QString strStatus;
  switch (status) {
    case BLK_SEC_STATUS_KX:
      strStatus = "空闲 ";
      break;
    case BLK_SEC_STATUS_ZY:
      strStatus = "占用";
      break;
    case BLK_SEC_STATUS_GZ:
      strStatus = "故障";
      break;
    case BLK_SEC_STATUS_SQFL:
      strStatus = "失去分路";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

QString DataUtils::getTcc2TccBlkSectLowFre(quint8 status)
{

    QString strStatus;
    switch (status) {
    case CODE_H:
        strStatus = "红";
        break;
    case CODE_HU:
        strStatus = "红黄";
        break;
    case CODE_HB:
        strStatus = "红白";
        break;
    case CODE_U:
        strStatus = "黄";
        break;
    case CODE_LU2:
        strStatus = "绿黄2 ";
        break;
    case CODE_LU:
        strStatus = "绿黄";
        break;
    case CODE_L:
        strStatus = "绿";
        break;
    case CODE_L2:
        strStatus = "绿2";
        break;
    case CODE_L3:
        strStatus = "绿3";
        break;
    case CODE_L4:
        strStatus = "绿4";
        break;
    case CODE_L5:
        strStatus = "绿5";
        break;
    case CODE_L6:
        strStatus = "绿6";
        break;
    case CODE_UU:
        strStatus = "黄黄";
        break;
    case CODE_UUS:
        strStatus = "黄黄闪";
        break;
    case CODE_U2:
        strStatus = "黄2";
        break;
    case CODE_U2S:
        strStatus = "U2S";
        break;
    case CODE_ZPQH:
        strStatus = "ZPQH";
        break;
    case CODE_ZYJC:
        strStatus = "ZYJC";
        break;
    default:
        strStatus = " ";
        break;
    }
    return strStatus;
}

QString DataUtils::getTsrs2TccTsrsType(quint8 status)
{
//#define CTRL_STATUS_YES 0xAA
//#define CTRL_STATUS_NO 0x55
  QString strStatus;
  switch (status) {
    case CTRL_STATUS_YES:
      strStatus = "YES";
      break;
    case CTRL_STATUS_NO:
      strStatus = "NO";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}
//#define TSR_REASON_WZ 0x11//限速原因 未知
//#define TSR_REASON_SG 0x22//限速原因 施工
//#define TSR_REASON_FYX 0x33//限速原因 风雨雪
//#define TSR_REASON_ZH 0x44//限速原因 突发灾害
QString DataUtils::getTsrs2TccTsrReason(quint8 status)
{
  QString strStatus;
  switch (status) {
    case TSR_REASON_WZ:
      strStatus = "未知 ";
      break;
    case TSR_REASON_SG:
      strStatus = "施工";
      break;
    case TSR_REASON_FYX:
      strStatus = "风雨雪";
      break;
    case TSR_REASON_ZH:
      strStatus = "突发灾害";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

//      //覆盖标示
//      #define COVER_FLAG_ZX 0x11//覆盖标示 正向
//      #define COVER_FLAG_FX 0x22//覆盖标示 反向
//      #define COVER_FLAG_BD 0x33//覆盖标示 本地
QString DataUtils::getTsrs2TccSPCoverFlag(quint8 status)
{
  QString strStatus;
  switch (status) {
    case COVER_FLAG_ZX:
      strStatus = "正向 ";
      break;
    case COVER_FLAG_FX:
      strStatus = "反向";
      break;
    case COVER_FLAG_BD:
      strStatus = "本地";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

QString DataUtils::getTsrs2TccEPCoverFlag(quint8 status)
{
  QString strStatus;
  switch (status) {
    case COVER_FLAG_ZX:
      strStatus = "正向 ";
      break;
    case COVER_FLAG_FX:
      strStatus = "反向";
      break;
    case COVER_FLAG_BD:
      strStatus = "本地";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

QString DataUtils::getTcc2TsrsBorderTsrCmdType(quint8 status)
{
  QString strStatus;
  switch (status) {
    case TSR_TYPE_CONFIRM:
      strStatus = "验证";
      break;
    case TSR_TYPE_EXECUTE:
      strStatus = "执行";
      break;
    default:
       strStatus = " ";
      break;
    }
  return strStatus;
}

QString DataUtils::getTcc2TsrsIsTsrInit(quint8 status)
{
  QString strStatus;
  switch (status) {
    case CTRL_STATUS_NO:
      strStatus = "初始化未完成";
      break;
    case CTRL_STATUS_YES:
      strStatus = "初始化完成";
      break;
    default:
      strStatus = " ";
      break;
    }
  return strStatus;


}

QString DataUtils::getTcc2TsrsBlockStatus(quint8 status)
{
  QString strStatus;
  switch (status) {
    case BLK_SEC_STATUS_ZY:
      strStatus = "占用";
      break;
    case BLK_SEC_STATUS_KX:
      strStatus = "空闲";
      break;
    case BLK_SEC_STATUS_GZ:
      strStatus = "故障";
      break;
    case BLK_SEC_STATUS_SQFL:
      strStatus = "失去分路";
      break;
    default:
      strStatus = " ";
      break;
    }
  return strStatus;
}

QString DataUtils::getFJSta(quint8 status)
{
    QString dir;
    switch (status)
    {
    case 0xaa:
        dir = "接车";
        break;
    case 0x55:
        dir = "发车";
        break;
    default:
        dir = "";
    }

    return dir;
}

QString DataUtils::getTsrsFlag(quint8 tsrId, quint8 speed)
{
    // format: id_speed
    return QString::number(tsrId) + "_" + QString::number(speed);
}

QString DataUtils::getTsrStatus(quint8 tsrStatus)
{
    //  执行状态, 0 = 无信息（不附加后续字节）;0x55 = 验证成功;0xA5 = 执行成功
    if (0 == tsrStatus)
    {
        return "无信息";
    }

    if (0x55 == tsrStatus)
    {
        return "验证成功";
    }

    if (0xa5 == tsrStatus)
    {
        return "执行成功";
    }

    return "执行失败";
}

QString DataUtils::cnvtBaliseSn(const QString &baliseSn)
{
    QString sn = "";

    for (QString data : baliseSn.split("-"))
    {
        sn += QString::number(data.toInt()) + "-";
    }

    // 去掉结尾-
    if (!sn.isEmpty())
    {
        sn.resize(sn.length()-1);
    }

    return sn;
}
