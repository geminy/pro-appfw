/**
 * @file ISystemDelegate.h
 * @brief class EISystemDelegate
 */

#ifndef EVO_ISYSTEMDELEGATE_H
#define EVO_ISYSTEMDELEGATE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

struct EAppConfig;
class EILayer;
class EIRootWindow;
class ECoreApplication;

/**
 * @class EISystemDelegate
 * @brief Interface for system delegate
 */
class EVO_APICALL EISystemDelegate
{
public:
    virtual ~EISystemDelegate() {}

    virtual ECoreApplication* createApplication(const EAppConfig &config) = 0;
    virtual VOID destroyApplication(ECoreApplication *app) = 0;
    virtual EIRootWindow* createRootWindow() = 0;
    virtual VOID destroyRootWindow(EIRootWindow *window) = 0;
    virtual EILayer* createGlobalLayer() = 0;
    virtual VOID destroyGlobalLayer(EILayer *layer) = 0;
};

#endif // EVO_ISYSTEMDELEGATE_H
