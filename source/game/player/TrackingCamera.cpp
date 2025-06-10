#include "game/player/TrackingCamera.h"
#include "engine/core/Engine.h"
#include "engine/core/Input.h"
#include "engine/core/VMath.h"
#include "game/core/Parameter.h"
#include "game/player/PlayerCore.h"
#include "game/player/PlayerHealthSystem.h"

void CameraHolder::onStart()
{
    player = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!player) {
        VDebuger::print("<ERROR> CAMERA_HOLDER :: ON_START :: player is nullptr");
        return;
    }


    playerHS = player->getComponent<PlayerHealthSystem>(true);

    if (!playerHS) {
        VDebuger::print("<ERROR> CAMERA_HOLDER :: ON_START :: playerHS is nullptr");
    }


    camera = getGame()->get_currentScene()->createObject<TrackingCamera>();
    this->addChild(camera);

    if (!camera) {
        VDebuger::print("<ERROR> CAMERA_HOLDER :: ON_START :: camera is nullptr");
        return;
    }

    camera->set_viewSize(Parameters::get_camera_viewSize());
    getGame()->get_currentScene()->set_mainCamera(camera);


    animController = createComponent<AnimationController>();


    //anims
    {
        auto t = camera->getTransformPtr();

        if (!t)
        {
            return;
        }


        //rotation

        auto am_shake01 = make_shared<AnimationTransformStep>(t,
                                                              t->get_localPosition(),
                                                              t->get_localPosition(),
                                                              t->get_scale(),
                                                              t->get_scale(),
                                                              t->get_rotation(),
                                                              t->get_rotation() + 10.f,
                                                              0.1f);

        auto am_shake02 = make_shared<AnimationTransformStep>(t,
                                                              t->get_localPosition(),
                                                              t->get_localPosition(),
                                                              t->get_scale(),
                                                              t->get_scale(),
                                                              t->get_rotation() + 10.f,
                                                              t->get_rotation() - 5.f,
                                                              0.1f);

        auto am_shake03 = make_shared<AnimationTransformStep>(t,
                                                              t->get_localPosition(),
                                                              t->get_localPosition(),
                                                              t->get_scale(),
                                                              t->get_scale(),
                                                              t->get_rotation() - 5.f,
                                                              t->get_rotation(),
                                                              0.1f);

        Animation anim_shake({ AnimationCycle( {am_shake01, am_shake02, am_shake03} ) });
        ANIM_SHAKE = animController->add(anim_shake);
    }

}

void CameraHolder::onUpdate(float dt)
{
    if (!player) {
        return;
    }

    float distance = getTransformPtr()->get_position().distanceTo(player->getTransformPtr()->get_position()) - Parameters::get_camera_trackingOff();

    Vector2 dir = player->getTransformPtr()->get_position() - getTransformPtr()->get_position();
    dir.normalize();

    float speed = Parameters::get_camera_speed() * dt * 0.0001 * distance;

    getTransformPtr()->add_position(dir * speed);

    //effects
    zoom(dt);
    //mapView(dt);
}


const bool CameraHolder::isOnScreen(const Vector2& point)
{
    if (!getGame() || !getGame()->get_window() || !getGame()->get_window()->get_renderwindow()) {
        VDebuger::print("<ERROR> TRACKING_CAMERA :: IS_ON_SCREEN :: nullptr");
        return false;
    }

    Vector2 winSize(getGame()->get_window()->get_renderwindow()->getSize().x * camera->get_viewSize(),
                    getGame()->get_window()->get_renderwindow()->getSize().y * camera->get_viewSize());

    Vector2 winZeroPos(getTransformPtr()->get_position() - (winSize * 0.5f));
    Vector2 winMaxPos(getTransformPtr()->get_position() + (winSize * 0.5f));

    return
        VMath::isInRange(point.x, winZeroPos.x, winMaxPos.x) &&
        VMath::isInRange(point.y, winZeroPos.y, winMaxPos.y);
}


void CameraHolder::shake()
{
    animController->play(ANIM_SHAKE);
}

void CameraHolder::zoom(const float& dt)
{
    if (!playerHS) {
        return;
    }

    bool zoom = playerHS->isHealing() && (camera->get_viewSize() > (0.4f * Parameters::get_camera_viewSize()));

    if (zoom)
    {
        camera->set_viewSize(camera->get_viewSize() - (dt * 0.001 * camera->get_viewSize()));
    }
    else if (!playerHS->isHealing() && camera->get_viewSize() < Parameters::get_camera_viewSize())
    {
        camera->set_viewSize(camera->get_viewSize() + (dt * 0.001));
    }
}

void CameraHolder::mapView(const float& dt)
{
    bool zoom = Input::Keyboard::isKeyPressed(Input::Keyboard::M) &&
                (camera->get_viewSize() < (10.f * Parameters::get_camera_viewSize()));

    if (zoom)
    {
        camera->set_viewSize(camera->get_viewSize() + (dt * 0.01));
    }
    else if (camera->get_viewSize() > Parameters::get_camera_viewSize())
    {
        camera->set_viewSize(camera->get_viewSize() - (dt * 0.01));
    }
}
