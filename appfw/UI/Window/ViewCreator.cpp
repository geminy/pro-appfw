#include "Definitions.h"
#include "log/Log.h"
#include "ui/View.h"
#include "ui/API.h"
#include "ui/ViewCreator.h"

EViewCreator::EViewCreator(const std::string &name)
    : EICreator(name)
{
    evo_logd(UI_LOG, "EViewCreator::EViewCreator %s", name.c_str());
}

EViewCreator::~EViewCreator()
{
    evo_logd(UI_LOG, "EViewCreator::~EViewCreator");
}

EIView* EViewCreator::create(const std::string &name)
{
    evo_logd(UI_LOG, "EViewCreator::create %s", name.c_str());

    return static_cast<EIView*>(EAPI::LoadQmlView(name));
}

VOID EViewCreator::destroy(EIView *view)
{
    evo_logd(UI_LOG, "EViewCreator::destroy");

    if (NULL != view) {
        evo_logd(UI_LOG, "EViewCreator::destroy %s", view->name().c_str());

        delete view;
        view = NULL;
    }
}
