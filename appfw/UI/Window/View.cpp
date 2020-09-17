#include "Definitions.h"
#include "log/Log.h"
#include "ui/View.h"

EView::EView(QQuickItem *parent)
    : EItem(parent)
    , EIView("")
{
    evo_logd(UI_LOG, "EView::EView");
}

EView::EView(const std::string &name, QQuickItem *parent)
    : EItem(parent)
    , EIView(name)
{
    evo_logd(UI_LOG, "EView::EView %s", name.c_str());
}

EView::~EView()
{
    evo_logd(UI_LOG, "EView::~EView");
}

VOID EView::onCreate()
{
    evo_logd(UI_LOG, "EView::onCreate begin");
    evo_logd(UI_LOG, "EView::onCreate end");
}

VOID EView::onActive()
{
    evo_logd(UI_LOG, "EView::onActive begin");

    setVisible(TRUE);

    evo_logd(UI_LOG, "EView::onActive end");
}

VOID EView::onDeactive()
{
    evo_logd(UI_LOG, "EView::onDeactive begin");

    setVisible(FALSE);

    evo_logd(UI_LOG, "EView::onDeactive end");
}

VOID EView::onDestroy()
{
    evo_logd(UI_LOG, "EView::onDestroy begin");
    evo_logd(UI_LOG, "EView::onDestroy end");
}

VOID EView::setViewName(const std::string &name)
{
    evo_logd(UI_LOG, "EView::onDestroy %s", name.c_str());

    m_name = name;
}
