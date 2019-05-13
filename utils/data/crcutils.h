#ifndef CRC_UTILS_H
#define CRC_UTILS_H

#include <QtGlobal>

class CrcUtils
{
public:
    static quint16 calculateCrc16(const QByteArray &data);
};

#endif // CRC_UTILS_H
