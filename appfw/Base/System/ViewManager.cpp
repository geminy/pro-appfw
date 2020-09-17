#include "Definitions.h"
#include "log/Log.h"
#include "base/IView.h"
#include "base/CoreApplication.h"
#include "base/CreatorManager.h"
#include "base/ViewManager.h"

EViewManager::EViewManager(ECoreApplication *app)
    : EAppContext(app)
{
    evo_logd(BASE_LOG, "EViewManager::EViewManager");
}

EViewManager::~EViewManager()
{
    evo_logd(BASE_LOG, "EViewManager::~EViewManager");
}

EIView* EViewManager::create(const std::string &name)
{
    evo_logd(BASE_LOG, "EViewManager::create %s", name.c_str());

    ViewCache::iterator it = m_viewCache.find(name);
    if (it != m_viewCache.end()) {
        return it->second;
    }

    ASSERT(NULL != context());
    ECreatorManager *cm = context()->creatorManager();
    ASSERT(NULL != cm);
    EIView *view = cm->create(name);
    ASSERT(NULL != view);
    view->onCreate();
    m_viewCache[name] = view;
    return view;
}

BOOL EViewManager::forward(const std::string &name)
{
    evo_logd(BASE_LOG, "EViewManager::forward %s", name.c_str());

    EIView *view = create(name);
    if (NULL != view) {
        view->onActive();
        return TRUE;
    }
    return FALSE;
}
