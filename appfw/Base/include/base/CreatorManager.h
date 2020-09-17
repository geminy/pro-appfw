/**
 * @file CreatorManager.h
 * @brief class ECreatorManager
 */

#ifndef EVO_CREATORMANAGER_H
#define EVO_CREATORMANAGER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/AppContext.h"

#include <string>

class EICreator;
class EIView;
class ECoreApplication;

/**
 * @class ECreatorManager
 * @brief App creator manager
 */
class EVO_APICALL ECreatorManager : public EAppContext
{
public:
    explicit ECreatorManager(ECoreApplication *app);
    ~ECreatorManager();

    BOOL registerCreator(EICreator &creator);
    BOOL unregisterCreator(EICreator &creator);

    EIView* create(const std::string &name);
    BOOL destroy(EIView *view);

private:
    EICreator *m_creator;
};

#endif // EVO_CREATORMANAGER_H
