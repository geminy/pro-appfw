#include <unistd.h>

#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "base/Thread.h"
#include "base/Mutex.h"
#include "base/Condition.h"
#include "base/RWLock.h"
#include "base/SpinLock.h"
#include "base/Barrier.h"
#include "TestBase.h"

#define TestBaseTag "TestBase"

TestBase::TestBase()
    : ETestSuite(TestBaseTag)
{
}

TestBase::~TestBase()
{
}

VOID TestBase::run()
{
    test_thread();
    test_mutex();
    test_cond();
    test_rwlock();
    test_spinlock();
    test_barrier();
}

static VOID* _Test_thread_routine(VOID *arg)
{
    evo_sleep(5);
    evo_logd(TestBaseTag, "_Test_thread_routine %d", *(INT32*)arg);

    EVO_UNUSED(arg);
    return NULL;
}

VOID TestBase::test_thread()
{
    EThread t;
    t.start();
    t.wait();
    evo_logd(TestBaseTag, "TestBase::test_thread default tid=%lu", t.getTid());

    EThread t2;
    INT32 arg = 100;
    t2.registerRoutine(_Test_thread_routine, &arg);
    t2.start();
    BOOL active = t2.isActive();
    evo_logd(TestBaseTag, "TestBase::test_thread routine tid=%lu active=%d", t2.getTid(), active);
    t2.terminate();
    active = t2.isActive();
    evo_logd(TestBaseTag, "TestBase::test_thread routine tid=%lu active=%d", t2.getTid(), active);
}

static INT32 _Test_mutex_count = 0;
static EMutex _Test_mutex_mutex;

static VOID* _Test_mutex_routine(VOID *arg)
{
    EAutoMutex mutex(&_Test_mutex_mutex);
    INT32 flag = *(INT32*)arg;
    for (INT32 i = 0; i < 10; ++i) {
        _Test_mutex_count += flag;
        usleep(1000);
        evo_logd(TestBaseTag, "_Test_mutex_routine %d", _Test_mutex_count);
    }

    EVO_UNUSED(arg);
    return NULL;
}

// simple test
VOID TestBase::test_mutex()
{
    EThread t;
    INT32 arg = 1;
    t.registerRoutine(_Test_mutex_routine, &arg);
    t.start();

    EThread t2;
    INT32 arg2 = 100;
    t2.registerRoutine(_Test_mutex_routine, &arg2);
    t2.start();

    t.wait();
    t2.wait();
}

static ECondition _Test_cond_cond;
static INT32 _Thread_cond_count = 0;
const INT32 _Thread_cond_count_max = 10;

static VOID* _Thread_cond_read(VOID *arg)
{
    EVO_UNUSED(arg);
    _Test_mutex_mutex.lock();
    if (_Thread_cond_count_max > _Thread_cond_count) {
        evo_logd(TestBaseTag, "_Thread_cond_read before %d", _Thread_cond_count);
        _Test_cond_cond.wait(_Test_mutex_mutex);
        evo_logd(TestBaseTag, "_Thread_cond_read after %d", _Thread_cond_count);
    }
    _Thread_cond_count = 0;
    _Test_mutex_mutex.unlock();
    return NULL;
}

static VOID* _Thread_cond_write(VOID *arg)
{
    EVO_UNUSED(arg);
    _Test_mutex_mutex.lock();
    while (_Thread_cond_count_max > _Thread_cond_count) {
        _Thread_cond_count++;
        evo_logd(TestBaseTag, "_Thread_cond_write before %d", _Thread_cond_count);
        _Test_cond_cond.signal();
        evo_logd(TestBaseTag, "_Thread_cond_write after %d", _Thread_cond_count);
    }
    _Test_mutex_mutex.unlock();
    return NULL;
}


VOID TestBase::test_cond()
{
    TID_T tid, tid2;
    evo_pthread_create(&tid, NULL, _Thread_cond_read, NULL);
    usleep(1000 * 500);
    evo_pthread_create(&tid2, NULL, _Thread_cond_write, NULL);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
}

static ERWLock _Rwlock;
static INT32 _Thread_rwlock_count = 0;
const INT32 _Thread_rwlock_count_max = 10;

static VOID* _Thread_rwlock_read(VOID *arg)
{
    _Rwlock.readLock();
    for (INT32 i = 0; i < 10; ++i) {
        evo_logd(TestBaseTag, "_Thread_rwlock_read %d %d %d", *(INT32*)arg, _Thread_rwlock_count, i);
        usleep(1000 * 100);
    }
    _Rwlock.unlock();
    return NULL;
}

static VOID* _Thread_rwlock_write(VOID *arg)
{
    EVO_UNUSED(arg);
    _Rwlock.writeLock();
    while (_Thread_rwlock_count_max > _Thread_rwlock_count) {
        _Thread_rwlock_count++;
        evo_logd(TestBaseTag, "_Thread_rwlock_write %d", _Thread_rwlock_count);
    }
    _Rwlock.unlock();
    return NULL;
}

// simple test
VOID TestBase::test_rwlock()
{
    TID_T tid, tid2, tid3;
    INT32 read = 1, read2 = 100;
    evo_pthread_create(&tid, NULL, _Thread_rwlock_read, &read);
    evo_pthread_create(&tid2, NULL, _Thread_rwlock_read, &read2);
    evo_pthread_create(&tid3, NULL, _Thread_rwlock_write, NULL);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
    evo_pthread_join(tid3, NULL);
}

static ESpinLock _Spinlock;
static INT32 _Thread_spinlock_count = 0;

static VOID* _Thread_spinlock_routine(VOID *arg)
{
    INT32 flag = *(INT32*)arg;
    _Spinlock.lock();
    for (INT32 i = 0; i < 10; ++i) {
        _Thread_spinlock_count += flag;
        evo_logd(TestBaseTag, "_Thread_spinlock_routine %d", _Thread_spinlock_count);
        usleep(1000);
    }
    _Spinlock.unlock();
    return NULL;
}

// simple test
VOID TestBase::test_spinlock()
{
    TID_T tid, tid2;
    INT32 read = 1, read2 = 100;
    evo_pthread_create(&tid, NULL, _Thread_spinlock_routine, &read);
    evo_pthread_create(&tid2, NULL, _Thread_spinlock_routine, &read2);
    evo_pthread_join(tid, NULL);
    evo_pthread_join(tid2, NULL);
}

static EBarrier _Barrier(5);
static EBarriers _Barriers;
const INT32 _Thread_barrier_thread = 5;

static VOID* _Thread_barrier_routine(VOID *arg)
{
    INT32 flag = *(INT32*)arg;
    _Barrier.wait();
    evo_logd(TestBaseTag, "_Thread_barrier_routine %d", flag);
    return NULL;
}

static VOID* _Thread_barriers_routine(VOID *arg)
{
    INT32 flag = *(INT32*)arg;
    _Barriers.wait();
    evo_logd(TestBaseTag, "_Thread_barriers_routine %d", flag);
    return NULL;
}

// simple test
VOID TestBase::test_barrier()
{
    TID_T threads[_Thread_barrier_thread];
    INT32 flags[_Thread_barrier_thread];
    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        flags[i] = i;
    }
    for (INT32 i = 0; i < _Thread_barrier_thread - 1; ++i) {
        evo_pthread_create(&threads[i], NULL, _Thread_barrier_routine, &flags[i]);
    }
    evo_sleep(1);
    evo_pthread_create(&threads[_Thread_barrier_thread - 1], NULL, _Thread_barrier_routine, &flags[_Thread_barrier_thread - 1]);
    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        evo_pthread_join(threads[i], NULL);
    }

    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        evo_pthread_create(&threads[i], NULL, _Thread_barriers_routine, &flags[i]);
    }
    _Barriers.open();
    for (INT32 i = 0; i < _Thread_barrier_thread; ++i) {
        evo_pthread_join(threads[i], NULL);
    }
    _Barriers.close();
}

EVO_TEST_RUN(TestBase)
