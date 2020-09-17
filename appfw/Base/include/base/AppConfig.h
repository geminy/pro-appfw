/**
 * @file AppConfig.h
 * @brief struct EAppConfig
 */

#ifndef EVO_APPCONFIG_H
#define EVO_APPCONFIG_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

/**
 * @struct EAppConfig
 * @brief App configuration
 */
struct EVO_APICALL EAppConfig
{
    std::string m_name;
    AppId m_id;

    EAppConfig()
        : m_name("default")
        , m_id(0)
    {
    }

    bool operator==(const EAppConfig &other) const
    {
        return m_name == other.m_name && m_id == other.m_id;
    }

    bool operator!=(const EAppConfig &other) const
    {
        return !(*this == other);
    }
};

#endif // EVO_APPFACTORY_H
