/**
 * @file ICreator.h
 * @brief class EICreator
 */

#ifndef EVO_ICREATOR_H
#define EVO_ICREATOR_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <string>

class EIView;

/**
 * @class EICreator
 * @brief Interface for app creator
 */
class EVO_APICALL EICreator
{
public:
    explicit EICreator(const std::string &name)
        : m_name(name)
    {
    }

    virtual ~EICreator() {}

    std::string name() const
    {
        return m_name;
    }

    virtual EIView* create(const std::string &name) = 0;
    virtual VOID destroy(EIView *view) = 0;

private:
    std::string m_name;
};

#endif // EVO_ICREATOR_H

