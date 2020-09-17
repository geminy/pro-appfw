/**
 * @file IApp.h
 * @brief class EIApp
 */

#ifndef EVO_IAPP_H
#define EVO_IAPP_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include <string>

#include "Global.h"

class EICreator;

/**
 * @class EIApp
 * @brief Interface for app
 */
class EVO_APICALL EIApp
{
public:
    explicit EIApp(std::string name)
        : m_name(name)
    {
    }

    virtual ~EIApp() {}

    std::string appName() const
    {
        return m_name;
    }

    virtual std::string startView() = 0;
    virtual EICreator* creator() = 0;

    virtual VOID onCreate() {}
    virtual VOID onInitialize() {}
    virtual VOID onActive() {}
    virtual VOID onDeactive() {}
    virtual VOID onFinalize() {}
    virtual VOID onDestroy() {}

protected:
    std::string m_name;
};

/**************************************************/

#define DECLARE_APPLICATION(Class) \
    EVO_DECLS_SINGLE EVO_APICALL EIApp* GetApplication() \
    { \
        return new (Class); \
    }

#endif // EVO_IAPP_H
