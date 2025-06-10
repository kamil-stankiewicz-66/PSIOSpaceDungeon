#ifndef PLAYERSPECIALEFFECTS_H
#define PLAYERSPECIALEFFECTS_H

#include "engine/component/Component.h"

class ParticleEffect;
class PlayerCore;

class PlayerSpecialEffects : public Component
{
    PlayerCore* playerCore = nullptr;
    ParticleEffect* parEff = nullptr;

    virtual void onAwake() override;
    virtual void onUpdate(float dt) override;
};

#endif // PLAYERSPECIALEFFECTS_H
