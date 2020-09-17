/**
 * @file AppLauncherBase.h
 * @brief class EAppLauncherBase and EIAppLauncherEntry
 */

#ifndef EVO_APPLAUNCHERBASE_H
#define EVO_APPLAUNCHERBASE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

struct EAppConfig;
class EISystem;
class EIApp;

/**
 * @class EAppLauncherBase
 * @brief Abstract class
 */
class EVO_APICALL EAppLauncherBase
{
public:
    EAppLauncherBase()
        : m_handle(NULL)
        , m_app(NULL)
    {
    }

    virtual ~EAppLauncherBase()
    {
        m_handle =  NULL;
        m_app = NULL;
    }

    virtual VOID* handle()
    {
        return m_handle;
    }

    virtual VOID loadLibrary(const CHAR *path) = 0;
    virtual VOID unloadLibrary() = 0;

    virtual EIApp* app()
    {
        return m_app;
    }

    virtual EIApp* loadApp(const CHAR *path) = 0;
    virtual VOID unloadApp() = 0;

    virtual VOID onUIInitialize(const EAppConfig &config) = 0;
    virtual VOID onUIFinalize() = 0;

    virtual VOID forwardStartView() = 0;
    virtual VOID show() = 0;
    virtual VOID hide() = 0;

protected:
    VOID *m_handle;
    EIApp *m_app;
};

/**
 * @class EIAppLauncherEntry
 * @brief Interface for app lancher entry
 */
class EVO_APICALL EIAppLauncherEntry
{
public:
    EIAppLauncherEntry() : m_launcher(NULL) {}
    virtual ~EIAppLauncherEntry() {}

    virtual VOID run() = 0;
    virtual VOID exit() = 0;

    virtual VOID onInitialize(EISystem *system) = 0;
    virtual VOID onFinalize() = 0;

    virtual EAppLauncherBase* appLauncher() { return m_launcher; }
    virtual EAppLauncherBase* createAppLauncher() = 0;
    virtual VOID destroyAppLauncher() = 0;

protected:
    EAppLauncherBase *m_launcher;
};

#endif // EVO_APPLAUNCHERBASE_H
