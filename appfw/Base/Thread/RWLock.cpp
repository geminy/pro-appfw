#include "wrapper/Wrapper.h"
#include "base/RWLock.h"

ERWLock::ERWLock()
{
    evo_pthread_rwlock_init(&m_rwlock, NULL);
}

ERWLock::ERWLock(EVO_UNUSED_PARAM const char *name)
{
    evo_pthread_rwlock_init(&m_rwlock, NULL);
}

ERWLock::ERWLock(RWLockAttr type, EVO_UNUSED_PARAM const char *name)
{
    if (SHARED == type) {
        pthread_rwlockattr_t attr;
        evo_pthread_rwlockattr_init(&attr);
        evo_pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        evo_pthread_rwlock_init(&m_rwlock, &attr);
        evo_pthread_rwlockattr_destroy(&attr);
    }
    else {
        evo_pthread_rwlock_init(&m_rwlock, NULL);
    }
}

ERWLock::~ERWLock()
{
    evo_pthread_rwlock_destroy(&m_rwlock);
}

VOID ERWLock::readLock()
{
    evo_pthread_rwlock_rdlock(&m_rwlock);
}

VOID ERWLock::tryReadLock()
{
    evo_pthread_rwlock_tryrdlock(&m_rwlock);
}

VOID ERWLock::writeLock()
{
    evo_pthread_rwlock_wrlock(&m_rwlock);
}

VOID ERWLock::tryWriteLock()
{
    evo_pthread_rwlock_trywrlock(&m_rwlock);
}

VOID ERWLock::unlock() {
    evo_pthread_rwlock_unlock(&m_rwlock);
}
