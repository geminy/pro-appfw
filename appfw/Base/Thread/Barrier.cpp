#include "wrapper/Wrapper.h"
#include "base/Barrier.h"

EBarrier::EBarrier(UINT32 count)
    : m_count(count)
{
    evo_pthread_barrier_init(&m_barrier, NULL, m_count);
}

EBarrier::~EBarrier()
{
    evo_pthread_barrier_destroy(&m_barrier);
}

VOID EBarrier::wait()
{
    evo_pthread_barrier_wait(&m_barrier);
}
