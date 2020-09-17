/**
 * @file Application.h
 * @brief class EApplication
 */

#ifndef EVO_APPLICATION_H
#define EVO_APPLICATION_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/CoreApplication.h"

class EFileLoader;
class EMainWindow;

/**
 * @class EApplication
 * @brief application
 */
class EVO_APICALL EApplication : public ECoreApplication
{
public:
    explicit EApplication(const EAppConfig &config);
    ~EApplication();

    EFileLoader* fileLoader() const;

    EMainWindow* mainWindow();
    EIMainWindow* createAndHideMainWindow();

private:
    class EApplicationContext;

    EApplicationContext *m_context;
};

#endif // EVO_APPLICATION_H
