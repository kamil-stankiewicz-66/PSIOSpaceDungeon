#ifndef PLAYERHEALTHSYSTEM_H
#define PLAYERHEALTHSYSTEM_H

#include "game/entity/HealthSystem.h"

class PlayerHealthSystem : public HealthSystem
{
    friend class PlayerCore;

public:
    virtual void onAwake() override;
};

#endif // PLAYERHEALTHSYSTEM_H
