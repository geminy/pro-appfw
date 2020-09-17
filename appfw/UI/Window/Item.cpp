#include "Definitions.h"
#include "log/Log.h"
#include "ui/Item.h"

EItem::EItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    evo_logd(UI_LOG, "EItem::EItem");
}

EItem::~EItem()
{
    evo_logd(UI_LOG, "EItem::~EItem");
}
