#ifndef PLAYERHEALTHSYSTEM_H
#define PLAYERHEALTHSYSTEM_H

#include "game/entity/HealthSystem.h"

class PlayerHealthSystem : public HealthSystem
{
    friend class PlayerCore;

private:
    float healPoints;
    float healPointsMax;

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

    //getters
    const float& getHealPoints() const;
    const float& getHealPointsMax() const;

};

#endif // PLAYERHEALTHSYSTEM_H
