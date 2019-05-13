#ifndef BYTE_ARRAY_UTILS_H
#define BYTE_ARRAY_UTILS_H

#include <QByteArray>

template<typename T>
class ByteArrayUtils
{
public:
    static void copyFromArray(T &dst, const QByteArray &src) {
        if (sizeof(T) != src.size())
        {
            return;
        }

        memcpy(&dst, src.data(), src.size());
    }

    static void copyToArray(QByteArray &dst, const T &src) {
        dst.resize(sizeof(T));
        memcpy(dst.data(), &src, sizeof(T));
    }
};

class ByteArrayUtils2
{
public:
    static void copyToArray(QByteArray &dst, quint8* src, quint32 len) {
        dst.resize(len);
        memcpy(dst.data(), src, len);
    }
};

#endif // BYTE_ARRAY_UTILS_H
