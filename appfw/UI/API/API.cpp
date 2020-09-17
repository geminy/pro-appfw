#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "base/ISystem.h"
#include "base/ICreator.h"
#include "base/AppAPI.h"
#include "ui/View.h"
#include "ui/MainWindow.h"
#include "ui/Application.h"
#include "ui/SystemDelegate.h"
#include "ui/FileLoader.h"
#include "ui/API.h"

namespace EAPI
{
    static EISystemDelegate *_SystemDelegate = NULL;

    VOID Initialize(EISystem *system)
    {
        evo_logd(UI_LOG, "EAPI::Initialize");

        if (NULL == system) {
            return;
        }
        if (NULL == _SystemDelegate) {
            _SystemDelegate = new ESystemDelegate;
        }

        EAppAPI::Initialize(_SystemDelegate);
    }

    VOID Finalize()
    {
        evo_logd(UI_LOG, "EAPI::Finalize");

        if (NULL != _SystemDelegate) {
            delete _SystemDelegate;
            _SystemDelegate = NULL;
        }
    }

    EApplication* GetApplication()
    {
        evo_logd(UI_LOG, "EAPI::GetApplication");

        return static_cast<EApplication*>(EAppAPI::GetApplication());
    }

    BOOL CreateApplication(const EAppConfig &config)
    {
        evo_logd(UI_LOG, "EAPI::CreateApplication %s", config.m_name.c_str());

        return EAppAPI::CreateApplication(config);
    }

    BOOL DestroyApplication()
    {
        evo_logd(UI_LOG, "EAPI::DestroyApplication");

        return EAppAPI::DestroyApplication();
    }

    VOID RegisterCreator(EICreator &creator)
    {
        evo_logd(UI_LOG, "EAPI::RegisterCreator %s" , creator.name().c_str());

        EAppAPI::RegisterCreator(creator);
    }

    VOID Show()
    {
        evo_logd(UI_LOG, "EAPI::Show");

        EApplication *app = GetApplication();
        if (app) {
            EMainWindow *window = app->mainWindow();
            if (window) {
                window->setWindowVisible(TRUE);
            }
        }
    }

    VOID Hide()
    {
        evo_logd(UI_LOG, "EAPI::Hide");

        EApplication *app = GetApplication();
        if (app) {
            EMainWindow *window = app->mainWindow();
            if (window) {
                window->setWindowVisible(FALSE);
            }
        }
    }

    VOID Forward(const std::string &name)
    {
        evo_logd(UI_LOG, "EAPI::Forward %s", name.c_str());

        EAppAPI::Forward(name);
    }

    EView* LoadQmlView(const std::string &name)
    {
        evo_logd(UI_LOG, "EAPI::LoadQmlView %s", name.c_str());

        EApplication *app = GetApplication();
        if (app && app->fileLoader()) {
            EView *view = app->fileLoader()->loadQmlView(name);
            if (NULL != view) {
                view->setVisible(TRUE);
            }
            return view;
        }
        return NULL;
    }
}
