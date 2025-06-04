#include "game/player/TrackingCamera.h"
#include "engine/core/Engine.h"
#include "game/core/Parameter.h"
#include "game/player/PlayerCore.h"

void TrackingCamera::onStart()
{
    player = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!player) {
        VDebuger::print("<ERROR> TRACKING_CAMERA :: ON_START :: player is nullptr");
    }
}

void TrackingCamera::onUpdate(float dt)
{
    if (!player) {
        return;
    }

    float distance = getTransformPtr()->get_position().distanceTo(player->getTransformPtr()->get_position()) - Parameters::get_camera_trackingOff();

    Vector2 dir = player->getTransformPtr()->get_position() - getTransformPtr()->get_position();
    dir.normalize();

    float speed = Parameters::get_camera_speed() * dt * 0.0001 * distance;

    getTransformPtr()->add_position(dir * speed);
}
