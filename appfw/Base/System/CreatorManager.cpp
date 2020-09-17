#include "Definitions.h"
#include "log/Log.h"
#include "base/ICreator.h"
#include "base/IView.h"
#include "base/CoreApplication.h"
#include "base/CreatorManager.h"

ECreatorManager::ECreatorManager(ECoreApplication *app)
    : EAppContext(app)
    ,m_creator(NULL)
{
    evo_logd(BASE_LOG, "ECreatorManager::ECreatorManager");
}

ECreatorManager::~ECreatorManager()
{
    evo_logd(BASE_LOG, "ECreatorManager::~ECreatorManager");

    m_creator = NULL;
}

BOOL ECreatorManager::registerCreator(EICreator &creator)
{
    evo_logd(BASE_LOG, "ECreatorManager::registerCreator %s", creator.name().c_str());

    if (NULL == m_creator) {
        m_creator = &creator;
        return TRUE;
    }
    return FALSE;
}

BOOL ECreatorManager::unregisterCreator(EICreator &creator)
{
    evo_logd(BASE_LOG, "ECreatorManager::unregisterCreator %s", creator.name().c_str());

    if (m_creator == &creator) {
        m_creator = NULL;
        return TRUE;
    }
    return FALSE;
}

EIView* ECreatorManager::create(const std::string &name)
{
    evo_logd(BASE_LOG, "ECreatorManager::create %s", name.c_str());

    if (NULL != m_creator) {
        return m_creator->create(name);
    }
    return NULL;
}

BOOL ECreatorManager::destroy(EIView *view)
{
    evo_logd(BASE_LOG, "ECreatorManager::destroy %s", view ? view->name().c_str() : "");

    if (NULL != m_creator) {
        m_creator->destroy(view);
        return TRUE;
    }
    return FALSE;
}
