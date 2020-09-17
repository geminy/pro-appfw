#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "base/ISystemDelegate.h"
#include "base/CoreApplication.h"
#include "base/AppManager.h"

/**
 * @class EAppManagerPrivate
 * @brief Private data for app manager
 */
class EAppManagerPrivate
{
public:
    EAppManagerPrivate()
        : systemDelegate(NULL)
        , app(NULL)
    {
    }

    ~EAppManagerPrivate()
    {
        systemDelegate = NULL;
        app = NULL;
    }

    EISystemDelegate *systemDelegate;
    ECoreApplication *app;
};

/**************************************************/

EAppManager::EAppManager(EISystemDelegate *systemDelegate)
    : m_private(new EAppManagerPrivate)
{
    evo_logd(BASE_LOG, "EAppManager::EAppManager");

    m_self = this;
    ASSERT(NULL != m_private);
    m_private->systemDelegate = systemDelegate;
}

EAppManager::~EAppManager()
{
    evo_logd(BASE_LOG, "EAppManager::~EAppManager");

    if (NULL != m_private) {
        delete m_private;
        m_private = NULL;
    }
    m_self = NULL;
}

EAppManager* EAppManager::m_self = NULL;

EAppManager* EAppManager::Instance()
{
    evo_logd(BASE_LOG, "EAppManager::Instance");

    return m_self;
}

ECoreApplication* EAppManager::getApplication() const
{
    evo_logd(BASE_LOG, "EAppManager::getApplication");

    ASSERT(NULL != m_private);
    return m_private->app;
}

BOOL EAppManager::createApplication(const EAppConfig &config)
{
    evo_logd(BASE_LOG, "EAppManager::createApplication");

    ASSERT(NULL != m_private);
    ASSERT(NULL != m_private->systemDelegate);
    ECoreApplication *app = m_private->systemDelegate->createApplication(config);
    if (NULL == app) {
        return FALSE;
    }
    m_private->app = app;
    return TRUE;
}

BOOL EAppManager::destroyApplication()
{
    evo_logd(BASE_LOG, "EAppManager::destroyApplication");

    ECoreApplication *app = getApplication();
    if (NULL == app) {
        return FALSE;
    }
    ASSERT(NULL != m_private);
    ASSERT(NULL != m_private->systemDelegate);
    m_private->systemDelegate->destroyApplication(app);
    return TRUE;
}
