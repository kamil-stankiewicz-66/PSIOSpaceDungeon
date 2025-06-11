#ifndef LEVELELEMENTS_H
#define LEVELELEMENTS_H

#include "engine/component/AnimationController.h"
#include "engine/object/Object.h"
#include "game/ui/Notification.h"

using uint = unsigned int;
class CircleCollider;
class ParticleEffect;
class LevelManager;


///
/// \brief Chest with coins.
///

class Chest : public GameObject
{
    friend class LevelManager;
    friend class LevelGenerator;

    //link
    NotificationManager* notificationManager = nullptr;

    //components
    CircleCollider* collider = nullptr;
    AnimationController* animContr = nullptr;

    //parts
    GameObject* body = nullptr;
    ParticleEffect* parEff = nullptr;

    //anims
    uint ANIM_OPEN;
    uint ANIM_EMPTY;

    //data
    bool m_isOpened;
    bool m_isLooted;
    uint coins;

    //engine
    virtual void onAwake() override;
    virtual void onUpdate(float) override;

    //actions
    void open();
    void empty();

    //setter - for level generator
    void set(const string_view txt_close,
             const string_view txt_open_full,
             const string_view txt_open_empty);

    void addCoins(const uint&);
};


///
/// \brief The FinishPoint class.
///

class FinishPoint : public GameObject
{
    //link
    LevelManager* levelManager = nullptr;

    //flag
    bool flag;

    //components
    CircleCollider* collider = nullptr;

    //engine
    virtual void onAwake() override;
    virtual void onUpdate(float) override;
};

#endif // LEVELELEMENTS_H
