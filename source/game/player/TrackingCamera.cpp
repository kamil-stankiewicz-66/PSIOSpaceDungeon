#include "game/player/TrackingCamera.h"
#include "engine/core/Engine.h"
#include "engine/core/VMath.h"
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


const bool TrackingCamera::isOnScreen(const Vector2& point)
{
    if (!getGame() || !getGame()->get_window() || !getGame()->get_window()->get_renderwindow()) {
        VDebuger::print("<ERROR> TRACKING_CAMERA :: IS_ON_SCREEN :: nullptr");
        return false;
    }

    Vector2 winSize(getGame()->get_window()->get_renderwindow()->getSize().x * get_viewSize(),
                    getGame()->get_window()->get_renderwindow()->getSize().y * get_viewSize());

    Vector2 winZeroPos(getTransformPtr()->get_position() - (winSize * 0.5f));
    Vector2 winMaxPos(getTransformPtr()->get_position() + (winSize * 0.5f));

    return
        VMath::isInRange(point.x, winZeroPos.x, winMaxPos.x) &&
        VMath::isInRange(point.y, winZeroPos.y, winMaxPos.y);
}
