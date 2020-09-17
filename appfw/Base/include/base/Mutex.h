/**
 * @file Mutex.h
 * @brief Mutex definitions
 */

#ifndef EVO_MUTEX_H
#define EVO_MUTEX_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <pthread.h>

class ECondition;

/**
 * @class EMutex
 * @brief Mutex definitions
 */
class EVO_APICALL EMutex
{
public:
    enum MutexAttr
    {
        PRIVATE,
        SHARED
    };

    EMutex();
    explicit EMutex(const char *name);
    explicit EMutex(MutexAttr type, const char *name = NULL);
    ~EMutex();

    VOID tryLock();
    VOID lock();
    VOID timedLock(INT64 nanosecond);
    VOID unlock();

    class EVO_APICALL EAutoLock
    {
    public:
        EAutoLock(EMutex &mutex) : m_lock(mutex)  { m_lock.lock(); }
        EAutoLock(EMutex *mutex) : m_lock(*mutex) { m_lock.lock(); }
        ~EAutoLock() { m_lock.unlock(); }

    private:
        EMutex &m_lock;
    };

private:
    friend class ECondition;

    EVO_DISABLE_COPY(EMutex)

    pthread_mutex_t m_mutex;
};

typedef EMutex::EAutoLock EAutoMutex;

#endif // EVO_MUTEX_H
