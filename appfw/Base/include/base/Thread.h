/**
 * @file Thread.h
 * @brief class EThread
 */

#ifndef EVO_THREAD_H
#define EVO_THREAD_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "Runnable.h"

/**
 * @class EThread
 * @brief Multi-thread
 */
class EVO_APICALL EThread : public ERunnable
{
public:
    typedef VOID*(*ThreadRoutine)(VOID*);

    EThread();
    ~EThread();

    VOID registerRoutine(ThreadRoutine routine, VOID *arg);
    TID_T getTid();
    BOOL isActive();

    VOID start();
    VOID wait();
    VOID terminate();

protected:
    VOID run();

private:
    EVO_DISABLE_COPY(EThread)

    ThreadRoutine m_routine;
    VOID *m_arg;
    TID_T m_tid;
    BOOL m_run;
};

#endif // EVO_THREAD_H
