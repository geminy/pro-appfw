#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "ui/Application.h"
#include "ui/RootWindow.h"
#include "ui/Layer.h"
#include "ui/SystemDelegate.h"

ESystemDelegate::ESystemDelegate()
{
    evo_logd(UI_LOG, "ESystemDelegate::ESystemDelegate");
}

ESystemDelegate::~ESystemDelegate()
{
    evo_logd(UI_LOG, "ESystemDelegate::~ESystemDelegate");
}

ECoreApplication* ESystemDelegate::createApplication(const EAppConfig &config)
{
    evo_logd(UI_LOG, "ESystemDelegate::createApplication %s", config.m_name.c_str());

    return new EApplication(config);
}

VOID ESystemDelegate::destroyApplication(ECoreApplication *app)
{
    evo_logd(UI_LOG, "ESystemDelegate::destroyApplication");

    if (NULL != app) {
        evo_logd(UI_LOG, "ESystemDelegate::destroyApplication %s", app->appName().c_str());

        delete app;
        app = NULL;
    }
}

EIRootWindow* ESystemDelegate::createRootWindow()
{
    evo_logd(UI_LOG, "ESystemDelegate::createRootWindow");

    return ERootWindow::Instance();
}

VOID ESystemDelegate::destroyRootWindow(EIRootWindow *window)
{
    evo_logd(UI_LOG, "ESystemDelegate::destroyRootWindow");

    if (NULL != window) {
        delete window;
        window = NULL;
    }
}

EILayer* ESystemDelegate::createGlobalLayer()
{
    evo_logd(UI_LOG, "ESystemDelegate::createGlobalLayer");

    ELayer *layer = new ELayer(0);
    layer->setObjectName("GlobalLayer");
    QQuickItem *parent = ERootWindow::Instance();
    ASSERT(NULL != parent);
    layer->setX(parent->x());
    layer->setY(parent->y());
    layer->setWidth(parent->width());
    layer->setHeight(parent->height());
    layer->setParentItem(parent);
    layer->setVisible(FALSE);

    return layer;
}

VOID ESystemDelegate::destroyGlobalLayer(EILayer *layer)
{
    evo_logd(UI_LOG, "ESystemDelegate::destroyGlobalLayer");

    if (NULL != layer) {
        evo_logd(UI_LOG, "ESystemDelegate::destroyGlobalLayer %d", layer->layerId());

        delete layer;
        layer = NULL;
    }
}
