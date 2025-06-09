#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include "engine/component/Component.h"
class Entity;


///
/// \brief Base health system.
///

class HealthSystem : public Component
{
private:
    float health;
    float healthMax;

protected:
    virtual void setHealth(const float& health);

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
