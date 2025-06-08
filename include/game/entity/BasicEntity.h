#ifndef BASICENTITY_H
#define BASICENTITY_H

#include "game/entity/Entity.h"

///
/// \brief Entity with basic attack.
///

class BasicEntity : public Entity
{
protected:

    //attack definition
    virtual void attack(const float& dt) override;

    //seek override
    virtual void seek(const float& dt) override;
};

#endif // BASICENTITY_H
