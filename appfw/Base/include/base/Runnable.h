/**
 * @file Runnable.h
 * @brief class ERunnable
 */

#ifndef EVO_RUNNABLE_H
#define EVO_RUNNABLE_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class ERunnable
 * @brief Abstract class
 */
class EVO_APICALL ERunnable
{
public:
    virtual ~ERunnable() {}

    virtual VOID run() = 0;
};

#endif // EVO_RUNNABLE_H
