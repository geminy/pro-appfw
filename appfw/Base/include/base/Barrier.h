/**
 * @file Barrier.h
 * @brief class EBarrier
 */

#ifndef EVO_BARRIER_H
#define EVO_BARRIER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/Mutex.h"
#include "base/Condition.h"

#include <pthread.h>

/**
 * @class EBarrier
 * @brief Barrier definitions
 */
class EVO_APICALL EBarrier
{
public:
    EBarrier(UINT32 count = 1);
    ~EBarrier();

    VOID wait();

private:
    EVO_DISABLE_COPY(EBarrier)

    pthread_barrier_t m_barrier;
    UINT32 m_count;
};

/**
 * @class EBarriers
 * @brief Barrier definitions
 */
class EVO_APICALL EBarriers
{
public:
    EBarriers()
        : m_state(BARRIER_CLOSED)
    {
    }

    ~EBarriers() {}

    VOID open()
    {
        EAutoMutex lock(m_mutex);
        m_state = BARRIER_OPENED;
        m_cond.broadcast();
    }

    VOID close()
    {
        EAutoMutex lock(m_mutex);
        m_state = BARRIER_CLOSED;
    }

    VOID wait() const
    {
        EAutoMutex lock(m_mutex);
        while (BARRIER_CLOSED == m_state) {
            m_cond.wait(m_mutex);
        }
    }

private:
    EVO_DISABLE_COPY(EBarriers)

    enum BarriersState
    {
        BARRIER_OPENED,
        BARRIER_CLOSED
    };

    mutable EMutex m_mutex;
    mutable ECondition m_cond;
    volatile BarriersState m_state;
};

#endif // EVO_BARRIER_H
