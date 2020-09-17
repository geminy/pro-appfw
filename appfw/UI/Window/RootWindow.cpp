#include "Definitions.h"
#include "log/Log.h"
#include "windowmanager/WindowManager.h"
#include "ui/RootWindow.h"

#include <QImage>

ERootWindow::ERootWindow(QQuickItem *parent)
    : EItem(parent)
{
    evo_logd(UI_LOG, "ERootWindow::ERootWindow");
}

ERootWindow::~ERootWindow()
{
    evo_logd(UI_LOG, "ERootWindow::~ERootWindow");
}

ERootWindow* ERootWindow::m_self = NULL;

ERootWindow* ERootWindow::Instance()
{
    evo_logd(UI_LOG, "ERootWindow::Instance");

    if (NULL == m_self) {
        m_self = new ERootWindow;
        m_self->setObjectName("RootWindow");
        QQuickItem *parent = EWindowManager::Instance()->content();
        ASSERT(NULL != parent);
        QQuickWindow *geo = EWindowManager::Instance()->window();
        ASSERT(NULL != geo);
        m_self->setX(geo->x());
        m_self->setY(geo->y());
        m_self->setWidth(geo->width());
        m_self->setHeight(geo->height());
        m_self->setParentItem(parent);
        m_self->setVisible(TRUE);
    }
    return m_self;
}

VOID ERootWindow::captureWindow()
{
    evo_logd(UI_LOG, "ERootWindow::captureWindow");

    QQuickWindow *window = EWindowManager::Instance()->window();
    ASSERT(NULL != window);
    QImage screenShot = window->grabWindow();
    BOOL ret = screenShot.save(UI_SCREENSHOT_NAME);
    evo_logd(UI_LOG, "ERootWindow::captureWindow result=%d", ret);
}
