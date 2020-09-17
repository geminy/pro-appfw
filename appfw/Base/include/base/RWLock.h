/**
 * @file RWLock.h
 * @brief RWLock definitions
 */

#ifndef EVO_RWLOCK_H
#define EVO_RWLOCK_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <pthread.h>

/**
 * @class ERWLock
 * @brief RWLock definitions
 */
class EVO_APICALL ERWLock
{
public:
    enum RWLockAttr
    {
        PRIVATE,
        SHARED
    };

    ERWLock();
    explicit ERWLock(const char *name);
    explicit ERWLock(RWLockAttr type, const char *name = NULL);
    ~ERWLock();

    VOID readLock();
    VOID tryReadLock();
    VOID writeLock();
    VOID tryWriteLock();
    VOID unlock();

    class EVO_APICALL EAutoRLock
    {
    public:
        EAutoRLock(ERWLock &rwlock) : m_lock(rwlock)  { m_lock.readLock(); }
        ~EAutoRLock() { m_lock.unlock(); }

    private:
        ERWLock &m_lock;
    };

    class EVO_APICALL EAutoWLock
    {
    public:
        EAutoWLock(ERWLock &rwlock) : m_lock(rwlock)  { m_lock.writeLock(); }
        ~EAutoWLock() { m_lock.unlock(); }

    private:
        ERWLock &m_lock;
    };

private:
    EVO_DISABLE_COPY(ERWLock)

    pthread_rwlock_t m_rwlock;
};

#endif // EVO_RWLOCK_H
