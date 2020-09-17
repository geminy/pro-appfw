/**
 * @file CoreApplication.h
 * @brief class ECoreApplication
 */

#ifndef EVO_COREAPPLICATION_H
#define EVO_COREAPPLICATION_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

struct EAppConfig;
class EIMainWindow;
class ECreatorManager;
class EViewManager;

/**
 * @class ECoreApplication
 * @brief Core application
 */
class EVO_APICALL ECoreApplication
{
public:
    explicit ECoreApplication(const EAppConfig &config);
    virtual ~ECoreApplication();

    std::string appName() const;

    EIMainWindow* mainWindow();

    virtual EIMainWindow* createAndHideMainWindow()
    {
        return NULL;
    }

    ECreatorManager* creatorManager();
    EViewManager* viewManger();

private:
    struct ECoreApplicationPrivate;

    ECoreApplicationPrivate *m_private;
};

#endif // EVO_COREAPPLICATION_H
