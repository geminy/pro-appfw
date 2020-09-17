#include "Definitions.h"
#include "log/Log.h"
#include "ui/MainWindow.h"

EMainWindow::EMainWindow(QQuickItem *parent)
    : EItem(parent)
{
    evo_logd(UI_LOG, "EMainWindow::EMainWindow");
}

EMainWindow::~EMainWindow()
{
    evo_logd(UI_LOG, "EMainWindow::~EMainWindow");
}

BOOL EMainWindow::windowVisible() const
{
    evo_logd(UI_LOG, "EMainWindow::windowVisible");

    return isVisible();
}

VOID EMainWindow::setWindowVisible(BOOL visible)
{
    evo_logd(UI_LOG, "EMainWindow::setWindowVisible %d", visible);

    setVisible(visible);
}

VOID EMainWindow::raiseSelf()
{
    evo_logd(UI_LOG, "EMainWindow::raiseSelf");

    QQuickItem *p = parentItem();
    if (NULL != p) {
        QList<QQuickItem*> childList = p->childItems();
        if (childList.length() > 0 && childList[0] != this) {
            stackBefore(childList[0]);
        }
    }
}

VOID EMainWindow::lowerSelf()
{
    evo_logd(UI_LOG, "EMainWindow::lowerSelf");

    QQuickItem *p = parentItem();
    if (NULL != p) {
        QList<QQuickItem*> childList = p->childItems();
        if (childList.length() > 0 && childList[childList.length() - 1] != this) {
            stackAfter(childList[childList.length() - 1]);
        }
    }
}

INT32 EMainWindow::windowX() const
{
    evo_logd(UI_LOG, "EMainWindow::windowX");

    return EVO_GEOMETRY_X;
}

INT32 EMainWindow::windowY() const
{
    evo_logd(UI_LOG, "EMainWindow::windowY");

    return EVO_GEOMETRY_Y;
}

INT32 EMainWindow::windowWidth() const
{
    evo_logd(UI_LOG, "EMainWindow::windowWidth");

    return EVO_GEOMETRY_WIDTH;
}

INT32 EMainWindow::windowHeight() const
{
    evo_logd(UI_LOG, "EMainWindow::windowHeight");

    return EVO_GEOMETRY_HEIGHT;
}
