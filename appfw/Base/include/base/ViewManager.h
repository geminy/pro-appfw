/**
 * @file ViewManager.h
 * @brief class EViewManager
 */

#ifndef EVO_VIEWMANAGER_H
#define EVO_VIEWMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/AppContext.h"

#include <string>
#include <map>

class EIView;
class ECoreApplication;

/**
 * @class EViewManager
 * @brief App view manager
 */
class EVO_APICALL EViewManager : public EAppContext
{
public:
    explicit EViewManager(ECoreApplication *app);
    ~EViewManager();

    EIView* create(const std::string &name);
    BOOL forward(const std::string &name);

private:
    typedef std::map<std::string, EIView*> ViewCache;
    ViewCache m_viewCache;
};

#endif // EVO_VIEWMANAGER_H
