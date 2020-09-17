/**
 * @file ISystem.h
 * @brief class EISystem
 */

#ifndef EVO_ISYSTEM_H
#define EVO_ISYSTEM_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EISystem
 * @brief Interface for system
 */
class EVO_APICALL EISystem
{
public:
    virtual ~EISystem() {}

    // TODO resolution
    virtual INT32 x() const = 0;
    virtual INT32 y() const = 0;
    virtual INT32 width() const = 0;
    virtual INT32 height() const = 0;
};

#endif // EVO_ISYSTEM_H
