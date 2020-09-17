/**
 * @file RootWindow.h
 * @brief class ERootWindow
 */

#ifndef EVO_ROOTWINDOW_H
#define EVO_ROOTWINDOW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/IRootWindow.h"
#include "ui/Item.h"

#include "QQuickView"

/**
 * @class ERootWindow
 * @brief Root window
 */
// class EVO_APICALL ERootWindow : public QQuickView, public EIRootWindow
class EVO_APICALL ERootWindow : public EItem, public EIRootWindow
{
    Q_OBJECT

public:
    explicit ERootWindow(QQuickItem *parent = 0);
    ~ERootWindow();

    static ERootWindow* Instance();

    VOID captureWindow();

private:
    static ERootWindow *m_self;
};

#endif // EVO_ROOTWINDOW_H
