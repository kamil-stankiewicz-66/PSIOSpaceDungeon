#ifndef PLAYERENEMYDETECTOR_H
#define PLAYERENEMYDETECTOR_H

#include "engine/component/Collider.h"
#include "engine/object/Camera.h"
#include "game/entity/Entity.h"
#include "game/level/Tilemap.h"

class PlayerCore;

///
/// \brief
///

class PlayerEnemyDetector : public GameObject
{
    friend PlayerCore;

private:
    PlayerCore* playerCore = nullptr;
    Camera* camera = nullptr;
    BoxCollider* boxCollider = nullptr;
    Tilemap* tilemap = nullptr;

    //current target
    Entity* target = nullptr;

protected:
    virtual void onAwake() override;
    virtual void onStart() override;
    virtual void onUpdate(float) override;

public:
    Entity* getTarget() const;
};

#endif // PLAYERENEMYDETECTOR_H
