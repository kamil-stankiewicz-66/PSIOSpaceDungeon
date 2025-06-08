#include "game/player/PlayerAttack.h"
#include "engine/core/Input.h"
#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"
#include "game/core/DataBlock.h"
#include "game/core/Tag.h"

void PlayerAttack::onAwake()
{
    playerCore = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!playerCore) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ATTACK :: playerCore = nullptr");
        return;
    }

    if (!playerCore->hand) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ATTACK :: playerCore is not inited");
        return;
    }

    weapon = Weapon::createWeapon(getGame()->get_currentScene(),
                                  *WeaponSO::get(PlayerData::weapon_id),
                                  Tag::ENEMY.data(),
                                  playerCore->getRenderLayer()+1u,
                                  playerCore->hand);
}

void PlayerAttack::onUpdate(float dt)
{
    if (!weapon) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ATTACK :: weapon is nullptr");
        return;
    }


    //weapon flip update
    weapon->getTransformPtr()->set_flip_x(playerCore->getTransformPtr()->get_localFlipX());


    if (!playerCore->playerDetector) {
        return;
    }


    //aim
    if (auto t = playerCore->playerDetector->getTarget())
    {
        Vector2 dir(t->getTransformPtr()->get_position() - playerCore->getTransformPtr()->get_position());
        dir.normalize();

        playerCore->getTransformPtr()->set_flip_x(dir.x < 0.0f);
        weapon->aim(t->getTransformPtr()->get_position());
    }
    else
    {
        weapon->resetAim();
    }

    //attack
    if (Input::Mouse::LEFT_BUTTON() || Input::Keyboard::isKeyPressed(Input::Keyboard::Key::Space)) {
        weapon->attack();
    }
}
