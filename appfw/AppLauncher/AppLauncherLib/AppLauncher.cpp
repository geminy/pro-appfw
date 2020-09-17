#include <dlfcn.h>

#include "Definitions.h"
#include "log/Log.h"
#include "AppPluginManager.h"
#include "AppLauncherManager.h"
#include "AppLauncher.h"

EAppLauncher::EAppLauncher(EAppPluginManager *plugin)
    : m_launchManager(new EAppLauncherManager(plugin))
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::EAppLauncher");
    ASSERT(NULL != m_launchManager);
}

EAppLauncher::~EAppLauncher()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::~EAppLauncher");

    if (NULL != m_launchManager) {
        delete m_launchManager;
        m_launchManager = NULL;
    }
}

VOID EAppLauncher::initialize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::initialize begin");

    if (NULL != m_launchManager) {
        m_launchManager->initialize();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::initialize end");
}

VOID EAppLauncher::run()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::run begin");

    if (NULL != m_launchManager) {
        m_launchManager->run();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::run end");
}

VOID EAppLauncher::finalize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::finalize begin");

    if (NULL != m_launchManager) {
        m_launchManager->finalize();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppLauncher::finalize end");
}

/**************************************************/

EVO_DECLS_SINGLE EVO_APICALL VOID mainloop(INT32 argc, CHAR **argv)
{
    evo_logd(APPLAUNCHERLIB_LOG, "mainloop begin");

    EAppLauncher launch(new EAppPluginManager(argc, argv));
    launch.initialize();
    launch.run();
    launch.finalize();

    evo_logd(APPLAUNCHERLIB_LOG, "mainloop end");
}
