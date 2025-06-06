#ifndef TRACKINGCAMERA_H
#define TRACKINGCAMERA_H

#include "engine/object/Camera.h"
class PlayerCore;

///
/// \brief Camera following the player.
///

class TrackingCamera : public Camera
{
    PlayerCore* player;
    bool m_isTracking;

    virtual void onStart() override;
    virtual void onUpdate(float dt) override;

public:
    const bool isOnScreen(const Vector2& point);
};

#endif // TRACKINGCAMERA_H
