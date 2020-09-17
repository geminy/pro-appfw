#include "NativeDefines.h"
#include "AppPlugin.h"

#include "log/Log.h"
#include "ui/View.h"

#include <QtQml>

EVO_AppPlugin::EVO_AppPlugin()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_AppPlugin::EVO_AppPlugin");

    initialize();
}

EVO_AppPlugin::~EVO_AppPlugin()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_AppPlugin::~EVO_AppPlugin");
}

VOID EVO_AppPlugin::initialize()
{
    evo_logd(NATIVE_QMLDEMO_LOG, "EVO_AppPlugin::initialize");

    qmlRegisterType<EView>("evo.views", 1, 0, "EView");
}
