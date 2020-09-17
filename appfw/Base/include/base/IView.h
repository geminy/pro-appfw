/**
 * @file IView.h
 * @brief class EIView
 */

#ifndef EVO_IVIEW_H
#define EVO_IVIEW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include <string>

#include "Global.h"

/**
 * @class EIView
 * @brief Interface for view
 */
class EVO_APICALL EIView
{
public:
    explicit EIView(const std::string &name)
        : m_name(name)
    {
    }

    virtual ~EIView() {}

    std::string name() const
    {
        return m_name;
    }

    virtual VOID onCreate() = 0;
    virtual VOID onActive() = 0;
    virtual VOID onDeactive() = 0;
    virtual VOID onDestroy() = 0;

protected:
    std::string m_name;
};

#endif // EVO_IVIEW_H

