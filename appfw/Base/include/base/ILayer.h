/**
 * @file ILayer.h
 * @brief class EILayer
 */

#ifndef EVO_ILAYER_H
#define EVO_ILAYER_H

#ifndef __cplusplus
# error ERROR: Only for cpp file.
#endif

#include "Global.h"

/**
 * @class EILayer
 * @brief Interface for app layer
 */
class EVO_APICALL EILayer
{
public:
    explicit EILayer(INT32 layerId)
        : m_layerId(layerId)
    {
    }

    virtual ~EILayer() {}

    INT32 layerId() const
    {
        return m_layerId;
    }

    VOID setLayerId(INT32 layerId)
    {
        m_layerId = layerId;
    }

    virtual BOOL layerVisible() const = 0;
    virtual VOID setLayerVisible(BOOL visible) = 0;

    virtual VOID raiseSelf() = 0;
    virtual VOID lowerSelf() = 0;

private:
    INT32 m_layerId;
};

#endif // EVO_ILAYER_H
