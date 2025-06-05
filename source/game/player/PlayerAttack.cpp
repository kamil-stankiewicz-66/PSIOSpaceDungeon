#include "game/player/PlayerAttack.h"
#include "engine/core/Input.h"
#include "engine/object/Camera.h"
#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"

void PlayerAttack::onAwake()
{
    playerCore = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!playerCore) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_MOVE :: playerCore = nullptr");
    }
}

void PlayerAttack::onUpdate(float dt)
{


    if (Input::Mouse::LEFT_BUTTON()){
        playerCore->weapon->attack();
    }
}
