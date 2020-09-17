#include "Definitions.h"
#include "log/Log.h"
#include "ui/Layer.h"

ELayer::ELayer(INT32 id, QQuickItem *parent)
    : EItem(parent)
    , EILayer(id)
{
    evo_logd(UI_LOG, "ELayer::ELayer");
}

ELayer::~ELayer()
{
    evo_logd(UI_LOG, "ELayer::~ELayer");
}

BOOL ELayer::layerVisible() const
{
    evo_logd(UI_LOG, "ELayer::layerVisible");

    return isVisible();
}

VOID ELayer::setLayerVisible(BOOL visible)
{
    evo_logd(UI_LOG, "ELayer::setLayerVisible %d", visible);

    setVisible(visible);
}

VOID ELayer::raiseSelf()
{
    evo_logd(UI_LOG, "ELayer::raiseSelf");

    QQuickItem *p = parentItem();
    if (NULL != p) {
        QList<QQuickItem*> childList = p->childItems();
        if (childList.length() > 0 && childList[0] != this) {
            stackBefore(childList[0]);
        }
    }
}

VOID ELayer::lowerSelf()
{
    evo_logd(UI_LOG, "ELayer::lowerSelf");

    QQuickItem *p = parentItem();
    if (NULL != p) {
        QList<QQuickItem*> childList = p->childItems();
        if (childList.length() > 0 && childList[childList.length() - 1] != this) {
            stackAfter(childList[childList.length() - 1]);
        }
    }
}
