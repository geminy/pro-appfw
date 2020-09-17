#include "NativeDefines.h"
#include "ViewController.h"

#include "log/Log.h"
#include "applauncher/IApp.h"

EVO_ViewController::EVO_ViewController()
    : EViewCreator(NATIVE_QMLDEMO_NAME)
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_ViewController::EVO_ViewController");
}

EVO_ViewController::~EVO_ViewController()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_ViewController::~EVO_ViewController");
}

std::string EVO_ViewController::startView()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_ViewController::startView %s", NATIVE_QMLDEMO_VIEW_HOME);

    return std::string(NATIVE_QMLDEMO_VIEW_HOME);
}
