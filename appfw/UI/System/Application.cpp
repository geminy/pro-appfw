#include "Definitions.h"
#include "log/Log.h"
#include "ui/FileLoader.h"
#include "ui/RootWindow.h"
#include "ui/MainWindow.h"
#include "ui/Application.h"

/**
 * @class EApplicationContext
 * @brief Private application context
 */
class EApplication::EApplicationContext
{
public:
    EApplicationContext(EApplication *app)
        : fileLoader(new EFileLoader)
    {
        EVO_UNUSED(app);
    }

    ~EApplicationContext()
    {
        if (NULL != fileLoader) {
            delete fileLoader;
            fileLoader = NULL;
        }
    }

    EFileLoader *fileLoader;
};

/**************************************************/

EApplication::EApplication(const EAppConfig &config)
    : ECoreApplication(config)
    , m_context(new EApplicationContext(this))
{
    evo_logd(UI_LOG, "EApplication::EApplication");
}

EApplication::~EApplication()
{
    evo_logd(UI_LOG, "EApplication::~EApplication");

    if (NULL != m_context) {
        delete m_context;
        m_context = NULL;
    }
}

EFileLoader* EApplication::fileLoader() const
{
    evo_logd(UI_LOG, "EApplication::fileLoader");

    ASSERT(NULL != m_context);
    return m_context->fileLoader;
}

EMainWindow* EApplication::mainWindow()
{
    evo_logd(UI_LOG, "EApplication::mainWindow");

    return static_cast<EMainWindow*>(ECoreApplication::mainWindow());
}

EIMainWindow* EApplication::createAndHideMainWindow()
{
    evo_logd(UI_LOG, "EApplication::createAndHideMainWindow");

    EMainWindow *window = new EMainWindow;
    window->setObjectName("MainWindow");
    QQuickItem *parent = ERootWindow::Instance();
    ASSERT(NULL != parent);
    window->setX(parent->x());
    window->setY(parent->y());
    window->setWidth(parent->width());
    window->setHeight(parent->height());
    window->setParentItem(parent);
    window->setVisible(FALSE);

    return window;
}
