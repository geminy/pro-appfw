/**
 * @file AppLauncher.h
 * @brief class EAppLauncher
 */

#ifndef EVO_APPLAUNCHER_H
#define EVO_APPLAUNCHER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class EAppPluginManager;
class EAppLauncherManager;

/**
 * @class EAppLauncher
 * @brief App launcher function
 */
class EVO_APICALL EAppLauncher
{
public:
    explicit EAppLauncher(EAppPluginManager *plugin);
    ~EAppLauncher();

    VOID initialize();
    VOID run();
    VOID finalize();

private:
    EVO_DISABLE_COPY(EAppLauncher)

    EAppLauncherManager *m_launchManager;
};

#endif // EVO_APPLAUNCHER_H
