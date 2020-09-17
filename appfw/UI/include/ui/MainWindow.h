/**
 * @file MainWindow.h
 * @brief class EMainWindow
 */

#ifndef EVO_MAINWINDOW_H
#define EVO_MAINWINDOW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/IMainWindow.h"
#include "ui/Item.h"

/**
 * @class EMainWindow
 * @brief Main window
 */
class EVO_APICALL EMainWindow : public EItem, public EIMainWindow
{
public:
    EMainWindow(QQuickItem *parent = 0);
    ~EMainWindow();

    BOOL windowVisible() const;
    VOID setWindowVisible(BOOL visible);

    VOID raiseSelf();
    VOID lowerSelf();

    INT32 windowX() const;
    INT32 windowY() const;
    INT32 windowWidth() const;
    INT32 windowHeight() const;
};

#endif // EVO_MAINWINDOW_H
