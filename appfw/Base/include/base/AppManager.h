/**
 * @file AppManager.h
 * @brief class EAppManager
 */

#ifndef EVO_APPMANAGER_H
#define EVO_APPMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

struct EAppConfig;
class EISystemDelegate;
class ECoreApplication;
class EAppManagerPrivate;

/**
 * @class EAppManager
 * @brief App manager
 */
class EVO_APICALL EAppManager
{
public:
    explicit EAppManager(EISystemDelegate *systemDelegate);
    ~EAppManager();

    static EAppManager* Instance();

    ECoreApplication* getApplication() const;
    BOOL createApplication(const EAppConfig &config);
    BOOL destroyApplication();

private:
    static EAppManager* m_self;

    EAppManagerPrivate *m_private;
};

#endif // EVO_APPMANAGER_H
