/**
 * @file SpinLock.h
 * @brief class ESpinLock
 */

#ifndef EVO_SPINLOCK_H
#define EVO_SPINLOCK_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <pthread.h>

/**
 * @class ESpinLock
 * @brief Spinlock definitions
 *
 * SpinLock:
 *     busy-wait-loop
 *     user mode
 *     more cpu
 *
 * Mutex:
 *     sleep
 *     kernel mode > user mode
 */
class EVO_APICALL ESpinLock
{
public:
    enum SpinLockAttr
    {
        PRIVATE,
        SHARED
    };

    explicit ESpinLock(SpinLockAttr type = PRIVATE);
    ~ESpinLock();

    VOID lock();
    VOID tryLock();
    VOID unlock();

private:
    EVO_DISABLE_COPY(ESpinLock)

    pthread_spinlock_t m_spin;
};

#endif // EVO_SPINLOCK_H
