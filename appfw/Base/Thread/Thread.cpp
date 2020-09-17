#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "base/Thread.h"

#include <cerrno>
#include <unistd.h>
#include <pthread.h>

VOID* _ThreadRoutine(VOID *f)
{
    ERunnable *r = static_cast<ERunnable*>(f);
    ASSERT(NULL != r);
    r->run();
    return NULL;
}

/**************************************************/

EThread::EThread()
    : m_routine(NULL)
    , m_arg(NULL)
    , m_run(FALSE)
{
}

EThread::~EThread()
{
    m_routine = NULL;
    m_arg = NULL;
}

VOID EThread::registerRoutine(ThreadRoutine routine, VOID *arg)
{
    ASSERT(NULL != routine);
    m_routine = routine;
    m_arg = arg;
}

TID_T EThread::getTid()
{
   return m_tid;
}

BOOL EThread::isActive()
{
    if (!m_run) {
        return FALSE;
    }

    INT32 ret = evo_pthread_kill(m_tid, 0);
    if (0 == ret) {
        return TRUE;
    }
    else if (ESRCH == ret) {
        return FALSE;
    }
    return FALSE;
}

VOID EThread::start()
{
    if (m_run) {
        return;
    }

    if (NULL != m_routine) {
        evo_pthread_create(&m_tid, NULL, m_routine, m_arg);
    }
    else {
        evo_pthread_create(&m_tid, NULL, _ThreadRoutine, this);
    }
    m_run = TRUE;
}

VOID EThread::wait()
{
    if (!m_run) {
        return;
    }

    if (isActive()) {
        evo_pthread_join(m_tid, NULL);
    }
}

VOID EThread::terminate()
{
    if (!m_run) {
        return;
    }

    if (isActive()) {
        evo_pthread_cancel(m_tid);
        // TODO sleep?
        usleep(1);
    }
}

VOID EThread::run()
{
    ASSERT(evo_pthread_self() == m_tid);
    evo_logd(BASE_LOG, "EThread::run");
}
