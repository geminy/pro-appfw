#include "wrapper/Wrapper.h"
#include "base/SpinLock.h"

ESpinLock::ESpinLock(SpinLockAttr type)
{
    evo_pthread_spin_init(&m_spin, type);
}

ESpinLock::~ESpinLock()
{
    evo_pthread_spin_destroy(&m_spin);
}

VOID ESpinLock::lock()
{
    evo_pthread_spin_lock(&m_spin);
}

VOID ESpinLock::tryLock()
{
    evo_pthread_spin_trylock(&m_spin);
}

VOID ESpinLock::unlock()
{
    evo_pthread_spin_unlock(&m_spin);
}
