#ifndef TRACKINGCAMERA_H
#define TRACKINGCAMERA_H

#include "engine/component/AnimationController.h"
#include "engine/object/Camera.h"
class PlayerCore;
class PlayerHealthSystem;

///
/// \brief Camera following the player.
///

class TrackingCamera : public Camera
{

};


///
/// \brief The CameraHolder class
///

class CameraHolder : public GameObject
{
    PlayerCore* player = nullptr;
    PlayerHealthSystem* playerHS = nullptr;
    TrackingCamera* camera = nullptr;

    bool m_isTracking;

    //anims
    uint ANIM_SHAKE;

    //component
    AnimationController* animController = nullptr;

    virtual void onStart() override;
    virtual void onUpdate(float dt) override;

    //effects
    void zoom(const float& dt);
    void mapView(const float& dt);

public:
    const bool isOnScreen(const Vector2& point);

    //effects
    void shake();
};

#endif // TRACKINGCAMERA_H
