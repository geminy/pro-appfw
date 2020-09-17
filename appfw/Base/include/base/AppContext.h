/**
 * @file AppContext.h
 * @brief class EAppContext
 */

#ifndef EVO_APPCONTEXT_H
#define EVO_APPCONTEXT_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

class ECoreApplication;

/**
 * @class EAppContext
 * @brief App context
 */
class EVO_APICALL EAppContext
{
public:
    explicit EAppContext(ECoreApplication *app)
        : m_app(app)
    {
    }

    virtual ~EAppContext()
    {
        m_app = NULL;
    }

    ECoreApplication* context() const
    {
        return m_app;
    }

private:
    ECoreApplication *m_app;
};

#endif // EVO_APPCONTEXT_H
