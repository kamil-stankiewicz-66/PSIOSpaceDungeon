#include "game/entity/BasicEntity.h"

void BasicEntity::attack(const float& dt)
{
    if (isPlayerInWeaponRange())
    {
        weaponCore->aim(player->get_position());
        weaponCore->attack();

        bool flip = (player->get_position() - weaponCore->getTransformPtr()->get_position()).x >= 0.0f;
        weaponCore->getTransformPtr()->set_flip_x(!flip);
    }
    else
    {
        moveTo(player->get_position(), entityData.runSpeed, dt);
        weaponCore->resetAim();
    }
}

void BasicEntity::seek(const float& dt)
{
    Entity::seek(dt);
    weaponCore->resetAim();
}
