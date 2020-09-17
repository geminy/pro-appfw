/**
 * @file AppForker.h
 * @brief class EAppFoker
 */

#ifndef EVO_APPFORKER_H
#define EVO_APPFORKER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EAppFocker
 * @brief Forks application
 */
class EVO_APICALL EAppFocker
{
public:
    EAppFocker();
    ~EAppFocker();

    VOID initialize();
    VOID finalize();

private:
    EVO_DISABLE_COPY(EAppFocker)
};

#endif // EVO_APPFORKER_H
