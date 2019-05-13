#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include "Public.h"

class DataUtils
{
public:
    static QString gbk2Utf8(const QString &inStr);
    static QString utf82Gbk(const QString &inStr);

    /*!
     * \brief pChar2String 字符数组转换成hex 字符串
     * \param src
     * \param len
     * \return
     */
    static QString pChar2HexString(const char *src, int len);
    static QString num2HexString(int num);

    /*!
     * \brief stringCopy QString -> STRING 转换
     * \param dst
     * \param src
     */
    static void stringCopy(STRING dst, const QString &src);

    /*!
     * \brief getCbiRouteSigShowDef 信号机显示含义
     * \param show
     * \param ok
     * \return
     */
    static quint8 getCbiRouteSigShowDef(const QString &show, bool *ok=0);

    static quint8 getCbiSignalOutStatusDef(const QString &show, bool *ok=0);

    /*!
     * \brief getCbiJZSglShiftSta 进站信号机红灯断丝
     * \param show
     * \param ok
     * \return
     */
    static quint8 getCbiJZSglShiftSta(const QString &show, bool *ok=0);

    /*!
     * \brief getCbiSglShutSta 信号机调车状态
     * \param show
     * \param ok
     * \return
     */
    static quint8 getCbiSglShutSta(const QString &show, bool *ok=0);

    static void initCbiSbStatusDef(UINT8 *cbiLockStatus);

    /*!
     * \brief getCbiSbStatusDef 区段锁闭状态
     * \param sb
     * \param ok
     * \return
     */
    static quint8 getCbiSbStatusDef(const QString &status, bool *ok=0);

    /*!
     * \brief getCbiFsjDef 发车锁闭
     * \param value
     * \param ok
     * \return
     */
    static quint8 getCbiFsjDef(const QString &value, bool *ok=0);

    /*!
     * \brief getCbiFqjDef 发车请求
     * \param value
     * \param ok
     * \return
     */
    static quint8 getCbiFqjDef(const QString &value, bool *ok=0);

    /*!
     * \brief getCbiJfajDef 接车辅助
     * \param value
     * \param ok
     * \return
     */
    static quint8 getCbiJfajDef(const QString &value, bool *ok=0);

    /*!
     * \brief getCbiFfajDef 发车辅助
     * \param value
     * \param ok
     * \return
     */
    static quint8 getCbiFfajDef(const QString &value, bool *ok=0);

    /*!
     * \brief getTccCodeOrderDef 边界区段码序
     * \param order
     * \param ok
     * \return
     */
    static quint8 getTccCodeOrderDef(const QString &order, bool *ok=0);

    /*!
     * \brief getTccLfDef 低频属性
     * \param lf
     * \param ok
     * \return
     */
    static quint8 getTccLfDef(const QString &lf, bool *ok=0);

    /*!
     * \brief getTccQdZyStatusDef 边界区段占用情况
     * \param qdZy
     * \param ok
     * \return
     */
    static quint8 getTccQdZyStatusDef(const QString &qdZy, bool *ok=0);

    /*!
     * \brief getTccSigBreakDef 防护信号机断丝
     * \param status
     * \param ok
     * \return
     */
    static quint8 getTccSigBreakDef(const QString &status, bool *ok=0);

    /*!
     * \brief getTccTsrCoverFlagDef tsrs覆盖标识
     * \param flag
     * \param ok
     * \return
     */
    static quint8 getTccTsrCoverFlagDef(const QString &coverFlag, bool *ok=0);

    /*!
     * \brief getTccChgDirDef tcc改方
     * \param value
     * \param ok
     * \return
     */
    static quint8 getTccChgDirDef(const QString &value, bool *ok=0);


    /*!
     * \brief getLcsZyStatusDef lcs区段占用状态
     * \param status
     * \param ok
     * \return
     */
    static quint8 getLcsZyStatusDef(const QString &status, bool *ok=0);



    /*!
     * \brief copyLcsBaliseMsg 经应答器报文字符串转化成128字节流
     * \param dst
     * \param src
     */
    static void copyLcsBaliseMsg(char dst[128], const QString &src);

    /*!
     * \brief getLcsRelayStatusDef 继电器状态定义
     * \param status
     * \param ok
     * \return
     */
    static quint8 getLcsRelayStatusDef(const QString &status, bool *ok=0);

    /*!
     * \brief getLcsTsrsStatusDef 临时限速状态
     * \param status
     * \param ok
     * \return
     */
    static quint8 getLcsTsrsStatusDef(const QString &status, bool *ok=0);

    static QString getFileName(const QString &path);

    static QString getLcsLfName(const quint8 lf);
    static QString getLcsCfName(const quint8 cf);

    static QString getUsercaseType(const QString &usercaseName);

    static QString getCbi2TccZoneDirStatus(quint8 status);
    static QString getCbi2TccRouteInfoStatus(quint8 status);
    static QString getCbi2TCCSiganlBrokenWire(quint8 status);
    static QString getCbi2TCCLineState(quint8 status);
    static QString getTccToCbiYFJInfo(quint8 status);
    static QString getTccToCbiSectionStatus(quint8 status);
    static QString getTccToCbiFZBLStatus(quint8 status);
    static QString getTccToCbiBLKStatus(quint8 status);
    static QString getTccToCbiSigTsrStatus(quint8 status);
    static QString getTccToCbiRedSignalBrokenWire(quint8 status);
    static QString getTccToCbiYWQXStatus(quint8 status);

    //tcc2tcc 边界区段灾害状态
    static QString getTcc2TccBoundaryZHSta(quint8 status);
    static quint8 getTcc2TccBoundaryZHSta(const QString &status);
    static QString getTcc2TccBoundaryBlkSta(quint8 status);
    static QString getTcc2TccSglHDErrSta(quint8 status);
    static QString getTcc2TccBlkLowFre(quint8 status);
    static QString getTcc2TccLowFreMode(quint8 status);
    static QString getTcc2TccBorderBlkStatus(quint8 status);
    static QString getTcc2TccSignalHDErrStatus(quint8 status);

    static quint8 getTccConnStatus(const QString &status);
    static quint8 getTccWorkStatus(const QString &status);
    static quint8 getTccMainCtrlStatus(const QString &status);
    static quint8 getTccblkInitStatus(const QString &status);
    static quint8 getTccLeuStatus(const QString &status);
    static quint8 getTccPermitStatus(const QString &status);
    static quint8 getTccPermitFlowStatus(const QString &status);
    static quint8 getTccZoneLogicCheckStatus(const QString &status);


    //线路改方信息
    static QString getTcc2TccZoneStatus(quint8 status);
    static QString getTcc2TccZoneRouteFlag(quint8 status);
    static QString getTcc2TccZoneFSJStatus(quint8 status);
    static QString getTcc2Tccuc_DePortDir(quint8 status);
    static QString getTcc2TccChgDirType(quint8 status);
    static QString getTcc2TccChgDirResult(quint8 status);

    //信号机状态
    static QString getTcc2TccSignalStatus(quint8 status);
    static quint8 getTcc2TccSignalStatus(const QString &status);

    //闭塞分区状态
    static QString getTcc2TccBlkSectStatus(quint8 status);

    //闭塞分区低频值
    static QString getTcc2TccBlkSectLowFre(quint8 status);


    //Tsrs -- tcc 的信息
    static QString getTsrs2TccTsrsType(quint8 status);
    static QString getTsrs2TccTsrReason(quint8 status);    //限速原因
    static QString getTsrs2TccSPCoverFlag(quint8 status);
    static QString getTsrs2TccEPCoverFlag(quint8 status);

   // tcc- tsrs
   //边界临时限速类型
    static QString getTcc2TsrsBorderTsrCmdType(quint8 status);
    static QString getTcc2TsrsIsTsrInit(quint8 status);
    static QString getTcc2TsrsBlockStatus(quint8 status);
    static QString getTcc2TsrsBlockLowFre(quint8 status);

    static QString getFJSta(quint8 status);


    /*!
     * \brief getTsrsFlag 根据tsrInfo结构，获得唯一能标识这条限速的flag
     * \param tsrInfo
     * \return
     */
    static QString getTsrsFlag(quint8 tsrId, quint8 speed);

    /*!
     * \brief getTsrStatus 获得tcc->tsrs执行结果
     * \param tsrStatus
     * \return
     */
    static QString getTsrStatus(quint8 tsrStatus);

    /*!
     * \brief cnvtBaliseSn 应答器编号转换 071-4-05-076-2 -> 71-4-5-76-2
     * \param baliseSn
     * \return
     */
    static QString cnvtBaliseSn(const QString &baliseSn);


};

#endif // DATA_UTILS_H
