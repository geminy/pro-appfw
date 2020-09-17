/**
 * @file AppFrameworkCallback.h
 * @brief class EAppFrameworkCallback
 */

#ifndef EVO_APPFRAMEWORKCALLBACK_H
#define EVO_APPFRAMEWORKCALLBACK_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/ISystem.h"

/**
 * @class EAppFrameworkCallback
 * @brief App framework callback
 */
class EVO_APICALL EAppFrameworkCallback : public EISystem
{
public:
    EAppFrameworkCallback();
    ~EAppFrameworkCallback();

    INT32 x() const;
    INT32 y() const;
    INT32 width() const;
    INT32 height() const;
};

#endif // EVO_APPFRAMEWORKCALLBACK_H
