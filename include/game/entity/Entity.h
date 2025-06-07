#ifndef ENTITY_H
#define ENTITY_H

#include "engine/component/AnimationController.h"
#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "game/physics/Rigidbody.h"
#include "game/weapon/Weapon.h"
#include <random>

using namespace std;
using uint = unsigned int;

enum class EntityState {
    Sleep, Attack, Seek
};


///
/// \brief Abstarct class for all entities.
///

class Entity : public GameObject
{
public:
    Entity(); //cntr

private:
    EntityState state;
    Tilemap* tilemap = nullptr;

    //anims
    uint ANIM_IDLE;
    uint ANIM_RUN;

    //vars for culculation
    Vector2 rndDirection;
    float rnd = 0.0f;
    float nextTime = 0.0f;
    float timeAcc = 0.0f;

    //engine
    virtual void onStart() override;
    virtual void onUpdate(float dt) override;

protected:

    //data
    EntityData entityData;

    //random engine
    mt19937 rng;

    //ptr
    Transform* weapon = nullptr;
    Transform* player = nullptr;

    //componets
    CircleCollider* collider = nullptr;
    Rigidbody* rb = nullptr;
    AnimationController* animController = nullptr;

    //weapon
    GameObject* hand = nullptr;
    Weapon* weaponCore = nullptr;


    //set data
    void set(const EntityData&);


private:
    void seek(const float& dt);

protected:

    ///
    /// \brief Defines fighting style.
    /// \param dt deltatime
    ///

    virtual void attack(const float& dt) = 0;

    //helpers
    float distanceToPlayer();
    bool isPlayerInVisionRange();
    bool isPlayerInWeaponRange();
    bool move(const Vector2& direction, const float& speed, const float& dt);
    bool moveTo(const Vector2& point, const float& speed, const float& dt);
};

#endif // ENTITY_H
