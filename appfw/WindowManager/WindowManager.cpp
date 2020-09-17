#include "Definitions.h"
#include "log/Log.h"
#include "windowmanager/WindowManager.h"

#include <QGuiApplication>
#include <QQuickWindow>
#include <QQuickView>
#include <QQuickItem>
#include <QtQml>

EWindowManager::EWindowManager()
    : m_app(NULL)
    , m_window(NULL)
    , m_screen(NULL)
    , m_engine(NULL)
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::EWindowManager");
}

EWindowManager::~EWindowManager()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::~EWindowManager");
}

EWindowManager* EWindowManager::m_self = NULL;

EWindowManager* EWindowManager::Instance()
{
    if (NULL == m_self) {
        m_self = new EWindowManager;
    }
    return m_self;
}

VOID EWindowManager::createApplication(INT32 argc, CHAR **argv)
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::createApplication");

    if (NULL == m_app) {
        m_app = new QGuiApplication(argc, argv);
    }
}

VOID EWindowManager::destroyApplication()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::destroyApplication");

    if (NULL != m_app) {
        delete m_app;
        m_app = NULL;
    }
}
INT32 EWindowManager::execApp()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::execApp");

    if (NULL != m_app) {
        return m_app->exec();
    }
    return -1;
}

VOID EWindowManager::exitApp(INT32 returnCode)
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::exitApp %d", returnCode);

    if (NULL != m_app) {
        m_app->exit(returnCode);
    }
}

VOID EWindowManager::quitApp()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::quitApp");

    if (NULL != m_app) {
        m_app->quit();
    }
}

VOID EWindowManager::createWindow()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::createWindow");

    if (NULL == m_window) {
        m_window = new QQuickWindow;
        m_window->setTitle(EVO_NAME);
        m_window->setGeometry(EVO_GEOMETRY_X, EVO_GEOMETRY_Y, EVO_GEOMETRY_WIDTH, EVO_GEOMETRY_HEIGHT);
        createEngine();
        createScreen();
        m_window->show();
    }
}

VOID EWindowManager::destroyWindow()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::destroyWindow");

    destroyScreen();
    destroyEngine();
    if (NULL != m_window) {
        delete m_window;
        m_window = NULL;
    }
}

QQuickWindow* EWindowManager::window()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::window");

    return m_window;
}

QQuickItem* EWindowManager::content()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::window");

    ASSERT(NULL != m_window);
    return m_window->contentItem();
}

QQmlEngine* EWindowManager::engine()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::engine");

    return m_engine;
}


VOID EWindowManager::createEngine()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::createEngine");

    if (NULL == m_engine) {
        m_engine = new QQmlEngine;
    }
}

VOID EWindowManager::destroyEngine()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::destroyEngine");

    if (NULL != m_engine) {
        delete m_engine;
        m_engine = NULL;
    }
}

VOID EWindowManager::createScreen()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::createScreen");

    if (NULL != m_window && NULL != m_engine) {
        QQmlComponent screen(m_engine, QUrl(WINDOWMANAGER_PATH_SCREEN));
        m_screen = qobject_cast<QQuickItem*>(screen.create());
        ASSERT(NULL != m_screen);
        m_screen->setParentItem(m_window->contentItem());
        m_screen->setVisible(TRUE);
    }
}

VOID EWindowManager::destroyScreen()
{
    evo_logd(WINDOWMANAGER_LOG, "EWindowManager::destroyScreen");

    if (NULL != m_screen) {
        delete m_screen;
        m_window = NULL;
    }
}
