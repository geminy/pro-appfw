#include "wrapper/Wrapper.h"
#include "base/Mutex.h"
#include "base/Condition.h"

ECondition::ECondition()
{
    evo_pthread_cond_init(&m_cond, NULL);
}

ECondition::ECondition(CondAttr type)
{
    if (SHARED == type) {
        pthread_condattr_t attr;
        evo_pthread_condattr_init(&attr);
        evo_pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        evo_pthread_cond_init(&m_cond, &attr);
        evo_pthread_condattr_destroy(&attr);
    }
    else {
        evo_pthread_cond_init(&m_cond, NULL);

    }
}

ECondition::~ECondition()
{
    evo_pthread_cond_destroy(&m_cond);
}

VOID ECondition::signal()
{
    evo_pthread_cond_signal(&m_cond);
}

VOID ECondition::signal(CondWakeUp type)
{
    if (COND_WAKEUP_ONE == type) {
        signal();
    }
    else {
        broadcast();
    }
}

VOID ECondition::broadcast()
{
    evo_pthread_cond_broadcast(&m_cond);
}

VOID ECondition::wait(EMutex &mutex)
{
    evo_pthread_cond_wait(&m_cond, &mutex.m_mutex);
}

VOID ECondition::timedwait(EMutex &mutex, INT64 nanosecond)
{
    const struct timespec ts = {
        /* .tv_sec = */ (nanosecond / 1000000000),
        /* .tv_nsec = */ (nanosecond % 1000000000)
    };
    evo_pthread_cond_timedwait(&m_cond, &mutex.m_mutex, &ts);
}
