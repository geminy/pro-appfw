#include "Definitions.h"
#include "log/Log.h"
#include "AppContext.h"
#include "AppContextManager.h"

EAppContextManager::EAppContextManager()
    : m_context(NULL)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContextManager::EAppContextManager");
}

EAppContextManager::~EAppContextManager()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContextManager::~EAppContextManager");

    if (NULL != m_context) {
        delete m_context;
        m_context = NULL;
    }
}

EAppContext* EAppContextManager::appContext()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContextManager::appContext");

    return m_context;
}

EAppContext* EAppContextManager::createAppContext(EAppLauncherBase *launcher)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContextManager::createAppContext");

    if (NULL == m_context) {
        m_context = new EAppContext(launcher);
    }
    return m_context;
}

VOID EAppContextManager::destroyAppConntext()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContextManager::destroyAppConntext");

    if (NULL != m_context) {
        delete m_context;
        m_context = NULL;
    }
}
