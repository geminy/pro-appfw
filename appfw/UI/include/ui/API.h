/**
 * @file API.h
 * @brief namespace EAPI
 */

#ifndef EVO_API_H
#define EVO_API_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

struct EAppConfig;
class EISystem;
class EICreator;
class EView;
class EApplication;

/**
 * @namespace EAPI
 * @brief Basic API
 */
namespace EAPI
{
    EVO_APICALL VOID Initialize(EISystem *);
    EVO_APICALL VOID Finalize();

    EVO_APICALL EApplication* GetApplication();
    EVO_APICALL BOOL CreateApplication(const EAppConfig &);
    EVO_APICALL BOOL DestroyApplication();

    EVO_APICALL VOID RegisterCreator(EICreator &);

    EVO_APICALL VOID Show();
    EVO_APICALL VOID Hide();

    EVO_APICALL VOID Forward(const std::string &);

    EVO_APICALL EView* LoadQmlView(const std::string &);
}

#endif // EVO_API_H
