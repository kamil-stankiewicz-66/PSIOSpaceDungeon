#include "game/player/PlayerMove.h"
#include "engine/core/Input.h"
#include "game/core/Parameter.h"
#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"
#include "engine/core/Scene.h"

void PlayerMove::onAwake()
{
    playerCore = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!playerCore) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_MOVE :: playerCore = nullptr");
    }
}

void PlayerMove::onUpdate(float dt)
{
    //set to (0,0)
    m_move_dir.clear();

    //get move direction
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::W)) {
        m_move_dir.y = 1.0f;
    }
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::S)) {
        m_move_dir.y = -1.0f;
    }
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::D)) {
        m_move_dir.x = 1.0f;
    }
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::A)) {
        m_move_dir.x = -1.0f;
    }

    //normalize
    m_move_dir.normalize();

    //move or not
    if (m_move_dir.x != 0.0f || m_move_dir.y != 0.0f) {
        move();
    }
}

void PlayerMove::move()
{
    auto _t = playerCore->getTransformPtr();

    if (!_t) {
        return;
    }

    _t->add_position(m_move_dir * Parameters::PlayerControl::getMoveSpeed());
    _t->set_flip_x(m_move_dir.x < 0);
}
