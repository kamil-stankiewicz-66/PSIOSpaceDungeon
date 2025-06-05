#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "engine/component/Component.h"
#include "engine/component/Transform.h"
#include "engine/core/Vector2.h"
#include "game/level/Tilemap.h"

///
/// \brief The physical component used to move objects, interacts with the tile map.
///

class Rigidbody : public Component
{
    Tilemap* tilemap;
    Transform* transform;
    Transform* rect;

    virtual void onStart() override;

public:
    void init(Transform* transform, Transform* rect);
    void addForce(const Vector2&);
};

#endif // RIGIDBODY_H
