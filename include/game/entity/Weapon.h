#ifndef WEAPON_H
#define WEAPON_H

#include "engine/component/Collider.h"
#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "game/core/ScriptableObject.h"
#include "game/level/Tilemap.h"
using uint = unsigned int;


///
/// \brief Abstract weapon class.
///

class Weapon : public GameObject
{
    WeaponData data;

private:
    float timeAcc;
    string targetTag;

    virtual void onUpdate(float dt) override;
    virtual void attackCore() = 0;

public:
    void attack();

    //aim to point
    virtual void aim(const Vector2& point) = 0;
    virtual void resetAim() = 0;

    //setter
    virtual void set(const WeaponData&, const string& targetTag);

    //damage
    void scaleDamage(const float&);

    //getter
    const float& getRange() const;
    const WeaponData& getData() const;
    const string& getTargetTag() const;


    //static
    static Weapon* createWeapon(Scene* scene, const WeaponData& data, const string& targetTag = "",
                                uint renderLayer = 0u, Object* parent = nullptr);
};


///
/// \brief The Melee class.
///

class Melee : public Weapon
{
    CircleCollider* collider = nullptr;

    //definitions
    virtual void attackCore() override;
    virtual void aim(const Vector2& point) override;
    virtual void resetAim() override;

public:
    //setter
    virtual void set(const WeaponData&, const string& targetTag) override;
};


///
/// \brief The Gun class.
///

class Gun : public Weapon
{
    //attack definition
    virtual void attackCore() override;

    //link
    Tilemap* tilemap = nullptr;

    //vars
    Vector2 aimDir;

public:
    //setter
    virtual void set(const WeaponData&, const string& targetTag) override;

    //aim to point
    virtual void aim(const Vector2& point) override;
    virtual void resetAim() override;
};


///
/// \brief The Bullet class.
///

class Bullet : public GameObject
{
    friend class Gun;
    CircleCollider* collider;
    string targetTag;

    //link
    Tilemap* tilemap = nullptr;

    float damage;
    Vector2 dir;

    //engine
    virtual void onUpdate(float dt);

    //init bullet from gun
    void init(const float& damage, const Vector2& dir, const string& targetTag, Tilemap* tilemap);

    //destroy
    void destroy(const sf::Color& color);

    //onDestroy effect
    void effect(const sf::Color& color);
};

#endif // WEAPON_H
