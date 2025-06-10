#ifndef PLAYERHEALTHSYSTEM_H
#define PLAYERHEALTHSYSTEM_H

#include "game/effect/ParticleEffect.h"
#include "game/entity/HealthSystem.h"
class LevelManager;
class CameraHolder;

class PlayerHealthSystem : public HealthSystem
{
    friend class PlayerCore;

private:
    float healPoints;
    float healPointsMax;

    //camera
    CameraHolder* camera = nullptr;

    //manager
    LevelManager* levelManager = nullptr;

    //particle effect
    ParticleEffect* parEff = nullptr;

    //flag
    bool m_isHealing;

    //heal bar
    Slider* healBar = nullptr;

    //engine
    virtual void onAwake() override;
    virtual void onUpdate(float dt) override;

    //private setters
    void setHealBar(Slider* slider);
    void setHealPoints(const float& v);
    void subHealPoints(const float&);

    //refresh
    void refreshHealBar();

public:
    void addHealPoints(const float&);
    virtual void addDamage(const float& damage) override;

    //getters
    const float& getHealPoints() const;
    const float& getHealPointsMax() const;
    const bool isHealing() const;

};

#endif // PLAYERHEALTHSYSTEM_H
