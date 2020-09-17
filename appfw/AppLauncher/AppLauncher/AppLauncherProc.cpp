#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "windowmanager/WindowManager.h"
#include "AppLauncherProc.h"

#include <dlfcn.h>

typedef VOID(*GetAppLauncher)(INT32 argc, CHAR **argv);

EAppLauncherProc::EAppLauncherProc(INT32 argc, CHAR **argv)
    : EProcessable(APPLAUNCHER_NAME, argc, argv)
    , m_argc(argc)
    , m_argv(argv)
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::EAppLauncherProc %s", m_name.c_str());
}

EAppLauncherProc::~EAppLauncherProc()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::~EAppLauncherProc");
}

VOID EAppLauncherProc::prepare4App()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::prepare4App begin");

    // TODO args?
    EWindowManager::Instance()->createApplication(0, NULL);

    EProcessable::initialize();
    EProcessable::start();

    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::prepare4App end");
}

VOID EAppLauncherProc::prepare4AppWindow()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::prepare4AppWindow begin");

    EWindowManager::Instance()->createWindow();

    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::prepare4AppWindow end");
}

VOID EAppLauncherProc::entryApp(INT32)
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::entryApp begin");

    VOID *appLauncher = evo_dlopen(APPLAUNCHER_SO, RTLD_LAZY | RTLD_LOCAL);
    ASSERT(NULL != appLauncher);
    GetAppLauncher loop = (GetAppLauncher)evo_dlsym(appLauncher, APPLANUCHER_MAINLOOP);
    ASSERT(NULL != loop);
    (*loop)(m_argc, m_argv);
    evo_dlclose(appLauncher);

//    EWindowManager::Instance()->execApp();

    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::entryApp begin end");
}

VOID EAppLauncherProc::clean4AppWindow()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::clean4AppWindow begin");

    EWindowManager::Instance()->destroyWindow();

    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::clean4AppWindow end");
}

VOID EAppLauncherProc::clean4App()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::clean4App begin");

    EProcessable::stop();
    EProcessable::finalize();

    EWindowManager::Instance()->destroyApplication();

    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::clean4App end");
}

VOID EAppLauncherProc::onInitialize()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onInitialize begin");
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onInitialize end");
}

VOID EAppLauncherProc::onStart()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onStart begin");
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onStart end");
}

VOID EAppLauncherProc::onStop()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onStop begin");
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onStop end");
}

VOID EAppLauncherProc::onFinalize()
{
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onFinalize begin");
    evo_logd(APPLAUNCHER_LOG, "EAppLauncherProc::onFinalize end");
}
