/**
 * @file AppAPI.h
 * @brief namespace EAppAPI
 */

#ifndef EVO_APPAPI_H
#define EVO_APPAPI_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

struct EAppConfig;
class EICreator;
class EISystemDelegate;
class ECoreApplication;

/**
 * @namespace EAPI
 * @brief Basic API
 */
namespace EAppAPI
{
    EVO_APICALL VOID Initialize(EISystemDelegate *);
    EVO_APICALL VOID Finalize();

    EVO_APICALL ECoreApplication* GetApplication();
    EVO_APICALL BOOL CreateApplication(const EAppConfig &);
    EVO_APICALL BOOL DestroyApplication();

    EVO_APICALL BOOL RegisterCreator(EICreator &);
    EVO_APICALL BOOL UnregisterCreator(EICreator &);

    BOOL Forward(const std::string &name);
}

#endif // EVO_APPAPI_H
