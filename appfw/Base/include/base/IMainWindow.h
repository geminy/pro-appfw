/**
 * @file IMainWindow.h
 * @brief class EIMainWindow
 */

#ifndef EVO_IMAINWINDOW_H
#define EVO_IMAINWINDOW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EIMainWindow
 * @brief Interface for app main window
 */
class EVO_APICALL EIMainWindow
{
public:
    virtual ~EIMainWindow() {}

    virtual BOOL windowVisible() const = 0;
    virtual VOID setWindowVisible(BOOL visible) = 0;

    virtual VOID raiseSelf() = 0;
    virtual VOID lowerSelf() = 0;

    // TODO geometry
    virtual INT32 windowX() const = 0;
    virtual INT32 windowY() const = 0;
    virtual INT32 windowWidth() const = 0;
    virtual INT32 windowHeight() const = 0;
};

#endif // EVO_IMAINWINDOW_H
