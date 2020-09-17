#include <dlfcn.h>

#include "Definitions.h"
#include "log/Log.h"
#include "AppContext.h"
#include "AppContextManager.h"
#include "AppPluginManager.h"
#include "AppFrameworkCallback.h"
#include "AppLauncherManager.h"

EAppLauncherManager::EAppLauncherManager(EAppPluginManager *plugin)
    : m_contextManager(new EAppContextManager)
    , m_pluginManager(plugin)
    , m_callback(new EAppFrameworkCallback)
    , m_initialized(FALSE)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::EAppLauncherManager");
    ASSERT(NULL != m_contextManager);
    ASSERT(NULL != m_pluginManager);

    m_self = this;
}

EAppLauncherManager::~EAppLauncherManager()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::~EAppLauncherManager");

    if (NULL != m_contextManager) {
        delete m_contextManager;
        m_contextManager = NULL;
    }

    if (NULL != m_pluginManager) {
        delete m_pluginManager;
        m_pluginManager = NULL;
    }

    if (NULL != m_callback) {
        delete m_callback;
        m_callback = NULL;
    }

    m_self = NULL;
}

EAppLauncherManager* EAppLauncherManager::m_self = NULL;

EAppLauncherManager* EAppLauncherManager::Instance()
{
    return m_self;
}

VOID EAppLauncherManager::initialize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::initialize begin");

    if (m_initialized) {
        return;
    }

    if (NULL != m_pluginManager && NULL != m_contextManager) {
        m_pluginManager->initialize(m_callback);
        EAppLauncherBase *launcher = m_pluginManager->appLauncher();
        if (NULL == launcher) {
            launcher = m_pluginManager->createAppLauncher();
        }
        EAppContext *context  = m_contextManager->appContext();
        if (NULL == context) {
            context = m_contextManager->createAppContext(launcher);
        }
        ASSERT(NULL != context);
        context->loadLibrary(APPLAUNCHERPLUGIN_SO_QMLDEMO);
        context->loadApp(APPLAUNCHERPLUGIN_SO_QMLDEMO);
        context->onCreate();
        context->onInitialize();
        context->onUIInitialize();
        context->onUIShow();
        m_initialized = TRUE;
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::initialize end");
}

VOID EAppLauncherManager::run()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::run begin");

    if (NULL != m_pluginManager) {
        m_pluginManager->run();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::run end");
}

VOID EAppLauncherManager::finalize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::finalize begin");

    if (!m_initialized) {
        return;
    }

    if (NULL != m_pluginManager && NULL != m_contextManager) {
        EAppContext *context = m_contextManager->appContext();
        ASSERT(NULL != context);
        context->onUIHide();
        context->onUIFinalize();
        context->onFinalize();
        context->onDestroy();
        context->unloadApp();
        context->unloadLibrary();
        m_contextManager->destroyAppConntext();
        m_pluginManager->destroyAppLauncher();
        m_pluginManager->finalize();
        m_initialized = FALSE;
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncherManager::finalize end");
}
