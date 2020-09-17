#include "wrapper/Wrapper.h"
#include "base/Mutex.h"

EMutex::EMutex()
{
    evo_pthread_mutex_init(&m_mutex, NULL);
}

EMutex::EMutex(EVO_UNUSED_PARAM const char *name)
{
    evo_pthread_mutex_init(&m_mutex, NULL);
}

EMutex::EMutex(MutexAttr type, EVO_UNUSED_PARAM const char *name)
{
    if (SHARED == type) {
        pthread_mutexattr_t attr;
        evo_pthread_mutexattr_init(&attr);
        evo_pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        evo_pthread_mutex_init(&m_mutex, &attr);
        evo_pthread_mutexattr_destroy(&attr);
    }
    else {
        evo_pthread_mutex_init(&m_mutex, NULL);
    }
}

EMutex::~EMutex()
{
    evo_pthread_mutex_destroy(&m_mutex);
}

VOID EMutex::tryLock()
{
    evo_pthread_mutex_trylock(&m_mutex);
}

VOID EMutex::lock()
{
    evo_pthread_mutex_lock(&m_mutex);
}

VOID EMutex::timedLock(INT64 nanosecond)
{
    const struct timespec ts = {
        /* .tv_sec = */ (nanosecond / 1000000000),
        /* .tv_nsec = */ (nanosecond % 1000000000)
    };
    evo_pthread_mutex_timedlock(&m_mutex, &ts);
}

VOID EMutex::unlock() {
    evo_pthread_mutex_unlock(&m_mutex);
}
