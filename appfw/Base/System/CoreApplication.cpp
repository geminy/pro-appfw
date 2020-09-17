#include "Definitions.h"
#include "log/Log.h"
#include "base/AppConfig.h"
#include "base/IMainWindow.h"
#include "base/CreatorManager.h"
#include "base/ViewManager.h"
#include "base/CoreApplication.h"

/**
 * @struct ECoreApplicationPrivate
 * @brief Private data for core application
 */
struct EVO_APICALL ECoreApplication::ECoreApplicationPrivate
{
    EAppConfig config;
    EIMainWindow *mainWindow;
    ECreatorManager creatorManagr;
    EViewManager viewManager;

    ECoreApplicationPrivate(const EAppConfig &_config, ECoreApplication *_context)
        : config(_config)
        , mainWindow(NULL)
        , creatorManagr(_context)
        , viewManager(_context)
    {
    }

    ~ECoreApplicationPrivate()
    {
        if (NULL != mainWindow) {
            delete mainWindow;
            mainWindow = NULL;
        }
    }
};

/**************************************************/

ECoreApplication::ECoreApplication(const EAppConfig &config)
    : m_private(new ECoreApplicationPrivate(config, this))
{
    evo_logd(BASE_LOG, "ECoreApplication::ECoreApplication %s", config.m_name.c_str());
}

ECoreApplication::~ECoreApplication()
{
    evo_logd(BASE_LOG, "ECoreApplication::~ECoreApplication");

    if (NULL != m_private) {
        delete m_private;
        m_private = NULL;
    }
}

std::string ECoreApplication::appName() const
{
    evo_logd(BASE_LOG, "ECoreApplication::appName");

    ASSERT(NULL != m_private);
    return m_private->config.m_name;
}

EIMainWindow* ECoreApplication::mainWindow()
{
    evo_logd(BASE_LOG, "ECoreApplication::mainWindow");

    ASSERT(NULL != m_private);
    if (NULL == m_private->mainWindow) {
        m_private->mainWindow = createAndHideMainWindow();
    }
    return m_private->mainWindow;
}

ECreatorManager* ECoreApplication::creatorManager()
{
    evo_logd(BASE_LOG, "ECoreApplication::creatorManager");

    ASSERT(NULL != m_private);
    return &(m_private->creatorManagr);
}

EViewManager* ECoreApplication::viewManger()
{
    evo_logd(BASE_LOG, "ECoreApplication::viewManger");

    ASSERT(NULL != m_private);
    return &(m_private->viewManager);
}
