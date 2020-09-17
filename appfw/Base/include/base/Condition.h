/**
 * @file Condition.h
 * @brief class ECondition
 */

#ifndef EVO_CONDITION_H
#define EVO_CONDITION_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <pthread.h>

class EMutex;

/**
 * @class ECondition
 * @brief Condition definitions
 */
class EVO_APICALL ECondition
{
public:
    enum CondAttr
    {
        PRIVATE,
        SHARED
    };

    enum CondWakeUp
    {
        COND_WAKEUP_ONE,
        COND_WAKEUP_ALL
    };

    ECondition();
    explicit ECondition(CondAttr type);
    ~ECondition();

    VOID signal();
    VOID signal(CondWakeUp type);
    VOID broadcast();

    VOID wait(EMutex &mutex);
    VOID timedwait(EMutex &mutex, INT64 nanosecond);

private:
    EVO_DISABLE_COPY(ECondition)

    pthread_cond_t m_cond;
};

#endif // EVO_CONDITION_H
