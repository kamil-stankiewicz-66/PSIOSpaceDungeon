#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "engine/object/Object.h"
#include "game/entity/Weapon.h"

class PlayerCore;

///
/// \brief Class that controls the player's attack.
///

class PlayerAttack : public Object
{
    friend PlayerCore;

private:
    PlayerCore* playerCore = nullptr;
    Weapon* weapon = nullptr;

protected:
    virtual void onAwake() override;
    virtual void onUpdate(float) override;
};

#endif // PLAYERATTACK_H
