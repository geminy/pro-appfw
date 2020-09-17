/**
 * @file IRootWindow.h
 * @brief class EIRootWindow
 */

#ifndef EVO_IROOTWINDOW_H
#define EVO_IROOTWINDOW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EIRootWindow
 * @brief Interface for app root window
 */
class EVO_APICALL EIRootWindow
{
public:
    virtual ~EIRootWindow() {}

    virtual VOID captureWindow() = 0;
};

#endif // EVO_IROOTWINDOW_H
