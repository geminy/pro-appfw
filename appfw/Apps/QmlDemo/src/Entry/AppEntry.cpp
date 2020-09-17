#include "NativeDefines.h"
#include "ViewController.h"
#include "AppPlugin.h"
#include "AppEntry.h"

#include "Global.h"
#include "log/Log.h"
#include "applauncher/IApp.h"

/**
 * @class EVO_NativeApp
 * @brief Native app entry
 */
class EVO_NativeApp : public EIApp
{
public:
    EVO_NativeApp();
    ~EVO_NativeApp();

    std::string startView();
    EICreator* creator();

    VOID onCreate();
    VOID onInitialize();
    VOID onActive();
    VOID onDeactive();
    VOID onFinalize();
    VOID onDestroy();

private:
    EVO_ViewController m_controller;
};

EVO_NativeApp::EVO_NativeApp()
    : EIApp(NATIVE_QMLDEMO_NAME)
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::EVO_NativeApp");
}

EVO_NativeApp::~EVO_NativeApp()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::~EVO_NativeApp");
}

std::string EVO_NativeApp::startView()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::startView");

    return m_controller.startView();
}

EICreator* EVO_NativeApp::creator()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::getCreator");

    return &m_controller;
}

VOID EVO_NativeApp::onCreate()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onCreate begin");

    EVO_AppPlugin();

    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onCreate end");
}

VOID EVO_NativeApp::onInitialize()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onInitialize begin");
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onInitialize end");
}

VOID EVO_NativeApp::onActive()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onActive");
}

VOID EVO_NativeApp::onDeactive()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onDeactive begin");
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onDeactive end");
}

VOID EVO_NativeApp::onFinalize()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onFinalize begin");
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onFinalize end");
}

VOID EVO_NativeApp::onDestroy()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onDestroy begin");
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_NativeApp::onDestroy end");
}

DECLARE_APPLICATION(EVO_NativeApp)
