#ifndef BASICENTITY_H
#define BASICENTITY_H

#include "game/entity/Entity.h"

///
/// \brief Entity with basic attack.
///

class BasicEntity : public Entity
{
protected:
    const float runSpeed = 4.0f;

    //attack definition
    virtual void attack(const float& dt) override;
};

#endif // BASICENTITY_H
