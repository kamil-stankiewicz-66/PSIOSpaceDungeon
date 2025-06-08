#ifndef LEVELELEMENTS_H
#define LEVELELEMENTS_H

#include "engine/component/AnimationController.h"
#include "engine/object/Object.h"

using uint = unsigned int;
class CircleCollider;


///
/// \brief Chest with coins.
///

class Chest : public GameObject
{
    friend class LevelManager;
    friend class LevelGenerator;

    //components
    CircleCollider* collider = nullptr;
    AnimationController* animContr = nullptr;

    //parts
    GameObject* body = nullptr;

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

    //setter - for level manager
    void set(const string_view txt_close,
             const string_view txt_open_full,
             const string_view txt_open_empty);
};


#endif // LEVELELEMENTS_H
