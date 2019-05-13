#ifndef SINGLETON_UTILS_H
#define SINGLETON_UTILS_H

#include <QMutex>
#include <QScopedPointer>

#define DECLARE_SINGLETON(Class) \
Q_DISABLE_COPY(Class) \
public: \
    static Class* instance() \
    { \
        static QMutex mutex; \
        static QScopedPointer<Class> inst; \
        if (Q_UNLIKELY(!inst)) { \
            mutex.lock(); \
            if (!inst) inst.reset(new Class); \
            mutex.unlock(); \
        } \
        return inst.data(); \
    }

#endif // SINGLETON_UTILS_H
