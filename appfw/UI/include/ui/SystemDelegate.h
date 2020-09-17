/**
 * @file SystemDelegate.h
 * @brief class ESystemDelegate
 */

#ifndef EVO_SYSTEMDELEGATE_H
#define EVO_SYSTEMDELEGATE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/ISystemDelegate.h"

/**
 * @class ESystemDelegate
 * @brief System delegate
 */
class EVO_APICALL ESystemDelegate : public EISystemDelegate
{
public:
    ESystemDelegate();
    ~ESystemDelegate();

    ECoreApplication* createApplication(const EAppConfig &config);
    VOID destroyApplication(ECoreApplication *app);
    EIRootWindow* createRootWindow();
    VOID destroyRootWindow(EIRootWindow *window);
    EILayer* createGlobalLayer();
    VOID destroyGlobalLayer(EILayer *layer);
};

#endif // EVO_SYSTEMDELEGATE_H
