#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "base/ICreator.h"
#include "base/ISystemDelegate.h"
#include "base/CoreApplication.h"
#include "base/AppManager.h"
#include "base/CreatorManager.h"
#include "base/ViewManager.h"
#include "base/AppAPI.h"

namespace EAppAPI
{
    static EAppManager *_AppManager = NULL;

    VOID Initialize(EISystemDelegate *delegate)
    {
        evo_logd(BASE_LOG, "EAppAPI::Initialize");

        if (NULL == delegate) {
            return;
        }
        if (NULL == _AppManager) {
            _AppManager = new EAppManager(delegate);
        }
    }

    VOID Finalize()
    {
        evo_logd(BASE_LOG, "EAppAPI::Finalize");

        if (NULL != _AppManager) {
            delete _AppManager;
            _AppManager = NULL;
        }
    }

    ECoreApplication* GetApplication()
    {
        evo_logd(BASE_LOG, "EAppAPI::GetApplication");

        ASSERT(NULL != _AppManager);
        return _AppManager->getApplication();
    }

    BOOL CreateApplication(const EAppConfig & config)
    {
        evo_logd(BASE_LOG, "EAppAPI::CreateApplication %s", config.m_name.c_str());

        ASSERT(NULL != _AppManager);
        return _AppManager->createApplication(config);
    }

    BOOL DestroyApplication()
    {
        evo_logd(BASE_LOG, "EAppAPI::DestroyApplication");

        ASSERT(NULL != _AppManager);
        return _AppManager->destroyApplication();
    }

    BOOL RegisterCreator(EICreator &creator)
    {
        evo_logd(BASE_LOG, "EAppAPI::RegisterCreator %s", creator.name().c_str());

        ASSERT(NULL != _AppManager);
        ECoreApplication *app = _AppManager->getApplication();
        ASSERT(NULL != app);
        ASSERT(NULL != app->creatorManager());
        return app->creatorManager()->registerCreator(creator);
    }

    BOOL UnregisterCreator(EICreator &creator)
    {
        evo_logd(BASE_LOG, "EAppAPI::UnregisterCreator %s", creator.name().c_str());

        ASSERT(NULL != _AppManager);
        ECoreApplication *app = _AppManager->getApplication();
        ASSERT(NULL != app);
        ASSERT(NULL != app->creatorManager());
        return app->creatorManager()->unregisterCreator(creator);
    }

    BOOL Forward(const std::string &name)
    {
        evo_logd(BASE_LOG, "EAppAPI::Forward %s", name.c_str());

        ASSERT(NULL != _AppManager);
        ECoreApplication *app = _AppManager->getApplication();
        ASSERT(NULL != app);
        ASSERT(NULL != app->viewManger());
        return app->viewManger()->forward(name);
    }
}
