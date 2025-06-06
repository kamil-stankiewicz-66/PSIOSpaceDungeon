#ifndef WEAPON_H
#define WEAPON_H

#include "engine/component/Collider.h"
#include "engine/object/Object.h"
using uint = unsigned int;

///
/// \brief Stores weapon data.
///

struct WeaponData
{
    uint id;
    string name;
    string textureRef;
    uint coins;

    float range;
    float damage;
    float attackTimeOut;
};


///
/// \brief Abstract weapon class.
///

class Weapon : public GameObject
{
    WeaponData data;

private:
    float timeAcc;

    virtual void onUpdate(float dt) override;
    virtual void attackCore() = 0;

public:
    void attack();

    //setter
    virtual void set(const WeaponData&);

    //getter
    const float& getRange() const;
    const WeaponData& getData() const;
};


///
/// \brief The Melee class.
///

class Melee : public Weapon
{
    CircleCollider* collider;
    virtual void attackCore() override;
};


///
/// \brief The Gun class.
///

class Gun : public Weapon
{
    //attack definition
    virtual void attackCore() override;

    //vars
    shared_ptr<sf::Texture> bulletTxt = nullptr;
    Vector2 aimDir;

public:
    //setter
    virtual void set(const WeaponData&) override;

    //aim to point
    void aim(const Vector2& point);
    void resetAim();
};


///
/// \brief The Bullet class.
///

class Bullet : public GameObject
{
    friend class Gun;
    CircleCollider* collider;

    float damage;
    Vector2 dir;

    //engine
    virtual void onUpdate(float dt);

    //init bullet from gun
    void init(const float& damage, const Vector2& dir);
};

#endif // WEAPON_H
