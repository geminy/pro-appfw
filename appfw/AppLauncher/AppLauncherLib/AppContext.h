/**
 * @file AppContext.h
 * @brief class EAppContext
 */

#ifndef EVO_APPCONTEXT_H
#define EVO_APPCONTEXT_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class EIApp;
class EAppLauncherBase;

/**
 * @class EAppContext
 * @brief App context
 */
class EVO_APICALL EAppContext
{
public:
    explicit EAppContext(EAppLauncherBase *launcher);
    ~EAppContext();

    VOID loadLibrary(const CHAR *path);
    VOID unloadLibrary();
    EIApp* app();
    EIApp* loadApp(const CHAR *path);
    VOID unloadApp();

    VOID onCreate();
    VOID onInitialize();
    VOID onFinalize();
    VOID onDestroy();

    VOID onUIInitialize();
    VOID onUIShow();
    VOID onUIHide();
    VOID onUIFinalize();

private:
    EVO_DISABLE_COPY(EAppContext)

    EAppLauncherBase *m_launcher;
};

#endif // EVO_APPCONTEXT_H
