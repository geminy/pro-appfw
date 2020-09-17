#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "applauncher/AppLauncherBase.h"
#include "AppFrameworkCallback.h"
#include "AppPluginManager.h"

#include <dlfcn.h>

typedef EIAppLauncherEntry*(*GetAppLauncherEntry)(INT32, CHAR**);

EAppPluginManager::EAppPluginManager(INT32 argc, CHAR **argv)
    : m_argc(argc)
    , m_argv(argv)
    , m_entry(NULL)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::EAppPluginManager");

    m_entry = loadAppLauncherEntry();
    ASSERT(NULL != m_entry);
}

EAppPluginManager::~EAppPluginManager()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::~EAppPluginManager");

    if (NULL != m_entry) {
        delete m_entry;
        m_entry = NULL;
    }
}

VOID EAppPluginManager::initialize(EAppFrameworkCallback *callback)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::initialize begin");

    if (NULL != m_entry) {
        m_entry->onInitialize(callback);
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::initialize end");
}

VOID EAppPluginManager::run()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::run begin");

    if (NULL != m_entry) {
        m_entry->run();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::run end");
}

VOID EAppPluginManager::finalize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::finalize begin");

    if (NULL != m_entry) {
        m_entry->onFinalize();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::finalize end");
}

VOID EAppPluginManager::exit()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::exit");

    if (NULL != m_entry) {
        m_entry->exit();
    }
}

EAppLauncherBase* EAppPluginManager::appLauncher()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::appLauncher");

    if (NULL != m_entry) {
        return m_entry->appLauncher();
    }
    return NULL;
}

EAppLauncherBase* EAppPluginManager::createAppLauncher()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::createAppLauncher");

    if (NULL != m_entry) {
        return m_entry->createAppLauncher();
    }
    return NULL;
}

VOID EAppPluginManager::destroyAppLauncher()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::destroyAppLauncher");

    if (NULL != m_entry) {
        m_entry->destroyAppLauncher();
    }
}

EIAppLauncherEntry* EAppPluginManager::loadAppLauncherEntry()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppPluginManager::loadAppLauncherEntry");

    VOID *plugin = evo_dlopen(APPLANUCHERLIB_SO, RTLD_LAZY);
    ASSERT(NULL != plugin);
    GetAppLauncherEntry entry = (GetAppLauncherEntry)evo_dlsym(plugin, APPLANUCHERLIB_PLUGIN);
    ASSERT(NULL != entry);

    return entry(m_argc, m_argv);
}
