#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "applauncher/AppLauncherBase.h"
#include "applauncher/IApp.h"
#include "AppContext.h"

EAppContext::EAppContext(EAppLauncherBase *launcher)
    : m_launcher(launcher)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::EAppContext");
    ASSERT(NULL != m_launcher);
}

EAppContext::~EAppContext()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::~EAppContext");
}

VOID EAppContext::loadLibrary(const CHAR *path)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::loadLibrary path=%s", path);

    if (NULL != m_launcher) {
        m_launcher->loadLibrary(path);
    }
}

VOID EAppContext::unloadLibrary()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::unloadLibrary");

    if (NULL != m_launcher) {
        m_launcher->unloadLibrary();
    }
}

EIApp* EAppContext::app()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::app");

    if (NULL != m_launcher) {
        return m_launcher->app();
    }
    return NULL;
}

EIApp* EAppContext::loadApp(const CHAR *path)
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::loadApp path=%s", path);

    if (NULL != m_launcher) {
        return m_launcher->loadApp(path);
    }
    return NULL;
}

VOID EAppContext::unloadApp()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::unloadApp");

    if (NULL != m_launcher) {
        m_launcher->unloadApp();
    }
}

VOID EAppContext::onCreate()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onCreate begin");

    if (app()) {
        app()->onCreate();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onCreate end");
}

VOID EAppContext::onInitialize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onInitialize begin");

    if (app()) {
        app()->onInitialize();
        app()->onActive();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onInitialize end");
}

VOID EAppContext::onFinalize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onFinalize begin");

    if (app()) {
        app()->onDeactive();
        app()->onFinalize();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onFinalize end");
}

VOID EAppContext::onDestroy()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onDestroy begin");

    if (app()) {
        app()->onDestroy();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onDestroy end");
}

VOID EAppContext::onUIInitialize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIInitialize begin");

    if (NULL != m_launcher) {
        EAppConfig config;
        if (app()) {
            config.m_name = app()->appName();
        }
        m_launcher->onUIInitialize(config);
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIInitialize end");
}

VOID EAppContext::onUIShow()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIShow begin");

    if (NULL != m_launcher) {
        m_launcher->forwardStartView();
        m_launcher->show();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIShow end");
}

VOID EAppContext::onUIHide()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIHide begin");

    if (NULL != m_launcher) {
        m_launcher->hide();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIHide end");
}

VOID EAppContext::onUIFinalize()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIFinalize begin");

    if (NULL != m_launcher) {
        m_launcher->onUIFinalize();
    }

    evo_logd(APPLAUNCHERLIB_LOG, "EAppContext::onUIFinalize end");
}
