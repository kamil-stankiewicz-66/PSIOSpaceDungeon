#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "engine/component/Component.h"
#include "game/ui/Slider.h"
class Entity;


///
/// \brief Base health system.
///

class HealthSystem : public Component
{
private:
    float health;
    float healthMax;

    //health bar
    Slider* healthBar = nullptr;

    //engine
    virtual void onAwake() override;

    //refresh health bar
    void refresh();

protected:
    virtual void setHealth(const float& health);
    void setHealthBar(Slider* slider);

public:
    virtual void addDamage(const float&);
    virtual void addHealth(const float&);

    const float& getHealth() const;
    const float& getHealthMax() const;
};


///
/// \brief Entity health system.
///

class EntityHealthSystem : public HealthSystem
{
    friend class Entity;

public:
    virtual void addDamage(const float&) override;
};

#endif // HEALTHSYSTEM_H
