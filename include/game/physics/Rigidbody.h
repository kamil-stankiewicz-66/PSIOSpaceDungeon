#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "engine/component/Collider.h"
#include "engine/component/Component.h"
#include "engine/component/Transform.h"
#include "engine/core/Vector2.h"
#include "game/level/Tilemap.h"

class Rigidbody : public Component
{
    Transform* transform;
    CircleCollider* collider;
    Tilemap* tilemap;

    virtual void onStart() override;

public:
    void addForce(const Vector2&);
};

#endif // RIGIDBODY_H
