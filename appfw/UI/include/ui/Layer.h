/**
 * @file Layer.h
 * @brief class ELayer
 */

#ifndef EVO_LAYER_H
#define EVO_LAYER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"
#include "base/ILayer.h"
#include "ui/Item.h"

/**
 * @class ELayer
 * @brief Layer
 */
class EVO_APICALL ELayer : public EItem, public EILayer
{
    Q_OBJECT

public:
    ELayer(INT32 id, QQuickItem *parent = 0);
    ~ELayer();

    BOOL layerVisible() const;
    VOID setLayerVisible(BOOL visible);

    VOID raiseSelf();
    VOID lowerSelf();
};

#endif // EVO_LAYER_H
