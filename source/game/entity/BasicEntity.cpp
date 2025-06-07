#include "game/entity/BasicEntity.h"

void BasicEntity::attack(const float& dt)
{
    if (isPlayerInWeaponRange()) {
        weaponCore->aim(player->get_position());
        weaponCore->attack();
    }
    else {
        moveTo(player->get_position(), entityData.runSpeed, dt);
        weaponCore->resetAim();
    }
}
