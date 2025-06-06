#include "game/entity/BasicEntity.h"

void BasicEntity::attack(const float& dt)
{
    if (isPlayerInWeaponRange()) {

    }
    else {
        moveTo(player->get_position(), runSpeed, dt);
    }
}
