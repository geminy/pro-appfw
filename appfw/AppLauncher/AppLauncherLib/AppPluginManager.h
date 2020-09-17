/**
 * @file AppPluginManager.h
 * @brief class EAppPluginManager
 */

#ifndef EVO_APPPLUGINMANAGER_H
#define EVO_APPPLUGINMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class EAppLauncherBase;
class EIAppLauncherEntry;
class EAppFrameworkCallback;

/**
 * @class EAppPluginManager
 * @brief App plugin manager
 */
class EVO_APICALL EAppPluginManager
{
public:
    EAppPluginManager(INT32 argc, CHAR **argv);
    ~EAppPluginManager();

    VOID initialize(EAppFrameworkCallback *callback);
    VOID run();
    VOID finalize();
    VOID exit();

    EAppLauncherBase* appLauncher();
    EAppLauncherBase* createAppLauncher();
    VOID destroyAppLauncher();

private:
    EIAppLauncherEntry* loadAppLauncherEntry();

private:
    EVO_DISABLE_COPY(EAppPluginManager)

    INT32 m_argc;
    CHAR **m_argv;
    EIAppLauncherEntry *m_entry;
};

#endif // EVO_APPPLUGINMANAGER_H
