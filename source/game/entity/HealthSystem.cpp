#include "game/entity/HealthSystem.h"
#include "engine/object/Object.h"


///
/// HealthSystem
///

void HealthSystem::setHealth(const float& health)
{
    this->health = health;

    if (health > healthMax) {
        this->healthMax = health;
    }
}


void HealthSystem::addDamage(const float& damage)
{
    health -= damage;

    if (health < 0.0f) {
        health = 0.0f;
    }
}

void HealthSystem::addHealth(const float& heal)
{
    health += heal;

    if (health > healthMax) {
        health = healthMax;
    }
}


const float& HealthSystem::getHealth() const {
    return health;
}

const float& HealthSystem::getHealthMax() const {
    return healthMax;
}


///
/// EntityHealthSystem
///

void EntityHealthSystem::addDamage(const float& damage)
{
    HealthSystem::addDamage(damage);

    if (getHealth() <= 0.0f)
    {
        if (!getObject()) {
            VDebuger::print("<ERROR> ENTITY_HEALTH_SYSTEM :: ADD_DAMAGE :: object is nullptr");
            return;
        }

        //kill
        getObject()->destroy(true);
    }
}
