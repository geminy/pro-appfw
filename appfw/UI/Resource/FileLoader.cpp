#include "Definitions.h"
#include "log/Log.h"
#include "windowmanager/WindowManager.h"
#include "ui/API.h"
#include "ui/MainWindow.h"
#include "ui/Application.h"
#include "ui/View.h"
#include "ui/FileLoader.h"

#include <QQmlComponent>
#include <QResource>

EFileLoader::EFileLoader()
{
    evo_logd(UI_LOG, "EFileLoader::EFileLoader");
}

EFileLoader::~EFileLoader()
{
    evo_logd(UI_LOG, "EFileLoader::~EFileLoader");
}

EView* EFileLoader::loadQmlView(const std::string &name)
{
    evo_logd(UI_LOG, "EFileLoader::loadQmlView %s", name.c_str());

    QString path = QString::fromStdString(viewName2Path(name));
    QQmlComponent component(EWindowManager::Instance()->engine(), QUrl(path));
    EView *view = qobject_cast<EView*>(component.create());
    if (NULL == view) {
        evo_logd(UI_LOG, "EFileLoader::loadQmlView error:%s", component.errorString().toStdString().c_str());
    }
    ASSERT(NULL != EAPI::GetApplication());
    view->setParentItem(static_cast<QQuickItem*>(EAPI::GetApplication()->mainWindow()));
    view->setVisible(FALSE);
    return view;
}

BOOL EFileLoader::isValidPath(const std::string &path) const
{
    evo_logd(UI_LOG, "EFileLoader::isValidPath %s", path.c_str());

    QResource res(QString::fromStdString(path));
    return res.isValid();
}

std::string EFileLoader::viewName2Path(const std::string &name) const
{
    evo_logd(UI_LOG, "EFileLoader::viewName2Path %s", name.c_str());

    std::string path("qrc://");
    path.append("/QmlDemo"); // TODO
    path.append("/");
    path.append(name);
    path.append(".qml");
    return path;
}
