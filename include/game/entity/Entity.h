#ifndef ENTITY_H
#define ENTITY_H

#include "engine/component/AnimationController.h"
#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "game/effect/AudioPlayer.h"
#include "game/effect/ParticleEffect.h"
#include "game/entity/HealthSystem.h"
#include "game/physics/Rigidbody.h"
#include "game/entity/Weapon.h"
#include "game/ui/Slider.h"
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
    friend class LevelGenerator;

public:
    Entity(); //cntr

private:
    EntityState state;
    Tilemap* tilemap = nullptr;

    //effect
    ParticleEffect* particleEfect = nullptr;
    AudioPlayer* audioPlayer = nullptr;

    //anims
    uint ANIM_IDLE;
    uint ANIM_RUN;

    //vars for culculation
    Vector2 rndDirection;
    float rnd = 0.0f;
    float nextTime = 0.0f;
    float timeAcc = 0.0f;

    //engine
    virtual void onAwake() override;
    virtual void onUpdate(float dt) override;
    virtual void onDestroy() override;

protected:

    //data
    EntityData entityData;

    //random engine
    mt19937 rng;

    //ptr
    Transform* player = nullptr;
    Slider* healthBar = nullptr;

    //componets
    BoxCollider* collider = nullptr;
    Rigidbody* rb = nullptr;
    AnimationController* animController = nullptr;
    EntityHealthSystem* healthSystem = nullptr;

    //weapon
    GameObject* body = nullptr;
    GameObject* hand = nullptr;
    Weapon* weaponCore = nullptr;


    //set data
    void set(const EntityData&);


protected:

    ///
    /// \brief Defines fighting style.
    /// \param dt deltatime
    ///

    virtual void attack(const float& dt) = 0;


    ///
    /// \brief Defines seek style.
    /// \param dt deltatime
    ///

    virtual void seek(const float& dt);


    //helpers
    float distanceToPlayer();
    bool isPlayerInVisionRange();
    bool isPlayerInWeaponRange();
    bool move(const Vector2& direction, const float& speed, const float& dt);
    bool moveTo(const Vector2& point, const float& speed, const float& dt);
};

#endif // ENTITY_H
