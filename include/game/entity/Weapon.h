#ifndef WEAPON_H
#define WEAPON_H

#include "engine/object/Object.h"

class Weapon : public GameObject
{
protected:
    float damage;

public:
    virtual void attack() = 0;
};


class Bullet : public GameObject
{
    friend class AssaultRifle;

private:
    float speed = 25.0f;
    float damage;
    Vector2 dir;
    void init(const float& damage, const float& rotation, bool flip);
    virtual void onUpdate(float dt);
};

class AssaultRifle : public Weapon
{
    float damage = 10.0f;

public:
    virtual void attack() override;
};

#endif // WEAPON_H
