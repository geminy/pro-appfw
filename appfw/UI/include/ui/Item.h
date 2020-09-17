/**
 * @file Item.h
 * @brief class EItem
 */

#ifndef EVO_ITEM_H
#define EVO_ITEM_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

#include <QQuickItem>

/**
 * @class EItem
 * @brief Basic item
 */
class EVO_APICALL EItem : public QQuickItem
{
    Q_OBJECT

public:
    explicit EItem(QQuickItem *parent = 0);
    virtual ~EItem();
};

#endif // EVO_ITEM_H
