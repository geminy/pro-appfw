/**
 * @file ViewCreator.h
 * @brief class EViewCreator
 */

#ifndef EVO_VIEWCREATOR_H
#define EVO_VIEWCREATOR_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/ICreator.h"

/**
 * @class EViewCreator
 * @brief View creator for app
 */
class EVO_APICALL EViewCreator : public EICreator
{
public:
    EViewCreator(const std::string &name);
    ~EViewCreator();

    EIView* create(const std::string &name);
    VOID destroy(EIView *view);
};

#endif // EVO_VIEWCREATOR_H
