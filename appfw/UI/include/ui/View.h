/**
 * @file View.h
 * @brief class EView
 */

#ifndef EVO_VIEW_H
#define EVO_VIEW_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/IView.h"
#include "ui/Item.h"

/**
 * @class EView
 * @brief Basic view
 */
class EVO_APICALL EView : public EItem, public EIView
{
    Q_OBJECT

public:
    explicit EView(QQuickItem *parent = 0);
    explicit EView(const std::string &name, QQuickItem *parent = 0);
    virtual ~EView();

    VOID onCreate();
    VOID onActive();
    VOID onDeactive();
    VOID onDestroy();

    VOID setViewName(const std::string &name);
};

#endif // EVO_VIEW_H
