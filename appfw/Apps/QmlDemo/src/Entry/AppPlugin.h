/**
 * @file AppPlugin.h
 * @brief class EVO_AppPlugin
 */

#ifndef EVO_APPPLUGIN_H
#define EVO_APPPLUGIN_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EVO_AppPlugin
 * @brief Native app plugin
 */
class EVO_AppPlugin
{
public:
    EVO_AppPlugin();
    ~EVO_AppPlugin();

private:
    VOID initialize();
};

#endif // EVO_APPPLUGIN_H
