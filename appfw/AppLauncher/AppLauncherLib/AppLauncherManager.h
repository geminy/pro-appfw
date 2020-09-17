/**
 * @file AppLauncherManager.h
 * @brief class EAppLauncherManager
 */

#ifndef EVO_APPLAUNCHERMANAGER_H
#define EVO_APPLAUNCHERMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class EAppContextManager;
class EAppPluginManager;
class EAppFrameworkCallback;

/**
 * @class EAppLauncherManager
 * @brief App lancher manager
 */
class EVO_APICALL EAppLauncherManager
{
public:
    explicit EAppLauncherManager(EAppPluginManager *plugin);
    ~EAppLauncherManager();

    static EAppLauncherManager* Instance();

    EAppContextManager* contextManager();
    EAppPluginManager* pluginManager();

    VOID initialize();
    VOID run();
    VOID finalize();

private:
    EVO_DISABLE_COPY(EAppLauncherManager)

    static EAppLauncherManager *m_self;

    EAppContextManager *m_contextManager;
    EAppPluginManager *m_pluginManager;
    EAppFrameworkCallback *m_callback;
    BOOL m_initialized;
};

#endif // EVO_APPLAUNCHERMANAGER_H
