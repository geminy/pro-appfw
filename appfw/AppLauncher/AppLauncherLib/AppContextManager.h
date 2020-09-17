/**
 * @file AppContextManager.h
 * @brief class EAppContextManager
 */

#ifndef EVO_APPCONTEXTMANAGER_H
#define EVO_APPCONTEXTMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class EAppContext;
class EAppLauncherBase;

/**
 * @class AppContextManager
 * @brief App context manager
 */
class EVO_APICALL EAppContextManager
{
public:
    EAppContextManager();
    ~EAppContextManager();

    EAppContext* appContext();
    EAppContext* createAppContext(EAppLauncherBase *launcher);
    VOID destroyAppConntext();

private:
    EVO_DISABLE_COPY(EAppContextManager)

    EAppContext *m_context;
};

#endif // EVO_APPCONTEXTMANAGER_H
