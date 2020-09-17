#include "Definitions.h"
#include "log/Log.h"
#include "AppFrameworkCallback.h"

EAppFrameworkCallback::EAppFrameworkCallback()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::EAppFrameworkCallback");
}

EAppFrameworkCallback::~EAppFrameworkCallback()
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::~EAppFrameworkCallback");
}

INT32 EAppFrameworkCallback::x() const
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::EAppFrameworkCallback x=%d", EVO_RESOLUTION_X);

    return EVO_RESOLUTION_X;
}

INT32 EAppFrameworkCallback::y() const
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::EAppFrameworkCallback y=%d", EVO_RESOLUTION_Y);

    return EVO_RESOLUTION_Y;
}

INT32 EAppFrameworkCallback::width() const
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::EAppFrameworkCallback width=%d", EVO_RESOLUTION_WIDTH);

    return EVO_RESOLUTION_WIDTH;
}

INT32 EAppFrameworkCallback::height() const
{
    evo_logd(APPLAUNCHERLIB_LOG, "EAppFrameworkCallback::EAppFrameworkCallback height=%d", EVO_RESOLUTION_HEIGHT);

    return EVO_RESOLUTION_HEIGHT;
}
