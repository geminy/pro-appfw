/**
 * @file WindowManager.h
 * @brief class EWindowManager
 */

#ifndef EVO_WINDOWMANAGER_H
#define EVO_WINDOWMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class QGuiApplication;
class QQuickWindow;
class QQuickItem;
class QQmlEngine;

/**
 * @class EWindowManager
 * @brief Window manager
 */
class EVO_APICALL EWindowManager
{
public:
    ~EWindowManager();

    static EWindowManager* Instance();

    VOID createApplication(INT32 argc, CHAR **argv);
    VOID destroyApplication();
    INT32 execApp();
    VOID exitApp(INT32 returnCode = 0);
    VOID quitApp();

    VOID createWindow();
    VOID destroyWindow();
    QQuickWindow* window();
    QQuickItem* content();
    QQmlEngine* engine();

private:
    EWindowManager();
    EVO_DISABLE_COPY(EWindowManager)

    VOID createEngine();
    VOID destroyEngine();

    VOID createScreen();
    VOID destroyScreen();

    static EWindowManager *m_self;

    QGuiApplication *m_app;
    QQuickWindow *m_window;
    QQuickItem *m_screen;
    QQmlEngine *m_engine;
};

#endif // EVO_WINDOWMANAGER_H
