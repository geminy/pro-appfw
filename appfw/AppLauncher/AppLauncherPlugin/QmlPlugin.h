/**
 * @file QmlPlugin.h
 * @brief Qml plugin
 */

#ifndef EVO_QMLPLUGIN_H
#define EVO_QMLPLUGIN_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include <string>

#include "Global.h"

struct EAppConfig;
class EISystem;
class EIApp;
class EAppLauncherBase;
class EIAppLauncherEntry;

/**
 * @class EQmlLauncher
 * @brief Qml launcher
 */
class EVO_APICALL EQmlLauncher : public EAppLauncherBase
{
public:
    EQmlLauncher();
    ~EQmlLauncher();

    VOID loadLibrary(const CHAR *path);
    VOID unloadLibrary();
    EIApp* loadApp(const CHAR *path);
    VOID unloadApp();

    VOID onUIInitialize(const EAppConfig &config);
    VOID onUIFinalize();

    VOID forwardStartView();
    VOID show();
    VOID hide();
};

/**
 * @class EQmlEntry
 * @brief Qml entry
 */
class EVO_APICALL EQmlEntry : public EIAppLauncherEntry
{
public:
    EQmlEntry(INT32 argc, CHAR **argv);
    ~EQmlEntry();

    VOID run();
    VOID exit();

    VOID onInitialize(EISystem *system);
    VOID onFinalize();

    EAppLauncherBase* createAppLauncher();
    VOID destroyAppLauncher();
};

#endif // EVO_QMLPLUGIN_H
