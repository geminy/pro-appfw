#include "Definitions.h"
#include "log/Log.h"
#include "wrapper/Wrapper.h"
#include "windowmanager/WindowManager.h"
#include "base/AppConfig.h"
#include "base/ISystem.h"
#include "applauncher/IApp.h"
#include "applauncher/AppLauncherBase.h"
#include "ui/API.h"
#include "QmlPlugin.h"

#include <dlfcn.h>

typedef EIApp*(*GetApplication)();

EQmlLauncher::EQmlLauncher()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::EQmlLauncher");
}

EQmlLauncher::~EQmlLauncher()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::~EQmlLauncher");
}

VOID EQmlLauncher::loadLibrary(const CHAR *path)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::loadLibrary %s", path);

    m_handle = evo_dlopen(path, RTLD_LAZY);
    ASSERT(NULL != m_handle);
}

VOID EQmlLauncher::unloadLibrary()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::unloadLibrary");

    if (NULL != m_handle) {
        evo_dlclose(m_handle);
        m_handle = NULL;
    }
}

EIApp* EQmlLauncher::loadApp(const CHAR *path)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::loadApp %s", path);

    GetApplication app = (GetApplication)evo_dlsym(m_handle, APPLAUNCHERPLUGIN_APP);
    ASSERT(NULL != app);

    m_app = app();
    ASSERT(NULL != m_app);

    return m_app;
}

VOID EQmlLauncher::unloadApp()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::unloadApp");

    if (NULL != m_app) {
        delete m_app;
        m_app = NULL;
    }
}

VOID EQmlLauncher::onUIInitialize(const EAppConfig &config)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::onUIInitialize begin");

    EAPI::CreateApplication(config);

    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::onUIInitialize end");
}

VOID EQmlLauncher::onUIFinalize()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::onUIFinalize begin");

    EAPI::DestroyApplication();

    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::onUIFinalize end");
}

VOID EQmlLauncher::forwardStartView()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::forwardStartView");

    ASSERT(NULL != m_app);
    EICreator *creator = m_app->creator();
    ASSERT(NULL != creator);
    EAPI::RegisterCreator(*creator);
    EAPI::Forward(m_app->startView());
}

VOID EQmlLauncher::show()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::show");

    EAPI::Show();
}

VOID EQmlLauncher::hide()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlLauncher::hide");

    EAPI::Hide();
}

/**************************************************/

EQmlEntry::EQmlEntry(INT32 argc, CHAR **argv)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::EQmlEntry");
    EVO_UNUSED(argc);
    EVO_UNUSED(argv);
}

EQmlEntry::~EQmlEntry()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::~EQmlEntry");
}

VOID EQmlEntry::run()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::run");

    EWindowManager::Instance()->execApp(); // TODO
}

VOID EQmlEntry::exit()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::exit");

   EWindowManager::Instance()->exitApp(); // TODO
}

VOID EQmlEntry::onInitialize(EISystem *system)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::onInitialize begin");

    EAPI::Initialize(system);

    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::onInitialize end");
}

VOID EQmlEntry::onFinalize()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::onFinalize begin");

    EAPI::Finalize();

    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::onFinalize end");
}

EAppLauncherBase* EQmlEntry::createAppLauncher()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::createAppLauncher");

    if (NULL == m_launcher) {
        m_launcher = new EQmlLauncher;
    }
    return m_launcher;
}

VOID EQmlEntry::destroyAppLauncher()
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "EQmlEntry::destroyAppLauncher");

    if (NULL != m_launcher) {
        delete  m_launcher;
        m_launcher = NULL;
    }
}

/**************************************************/

EVO_DECLS_SINGLE EVO_APICALL EIAppLauncherEntry*
GetAppLauncherEntry(INT32 argc, CHAR **argv)
{
    evo_logd(APPLAUNCHERPLUGIN_LOG, "GetAppLauncherEntry");

    return new EQmlEntry(argc, argv);
}
