#include "game/physics/Rigidbody.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"

void Rigidbody::onStart()
{
    if (!getObject()) {
        return;
    }

    transform = getObject()->getTransformPtr();
    collider = getObject()->getComponent<CircleCollider>(true);
    tilemap = getGame()->get_currentScene()->findObject<Tilemap>("tilemap");

    if (!transform || !tilemap || !collider) {
        VDebuger::print("<ERROR> RIGIDBODY :: ON_START :: collider or transform or tilemap is nullptr");
    }
}

void Rigidbody::addForce(const Vector2& force)
{
    if (!tilemap) {
        return;
    }

    if (!transform) {
        return;
    }

    if (!collider) {
        return;
    }


    float tileFactor = 1.0f;

    if (const Tile* tile = tilemap->getTileRealPos(transform->get_position().x, transform->get_position().y)) {
        tileFactor = tile->getExceedability();
    }
    else {
        tileFactor = 0.0f;
    }


    Vector2 potentialPosition(transform->get_position() + (force * tileFactor));
    Vector2 potentialColEdgePosition = potentialPosition.get_normalized() * (potentialPosition.modulo() + collider->getRadius());

    if (auto tile = tilemap->getTileRealPos(potentialColEdgePosition.x, potentialColEdgePosition.y))
    {
        if (tile->getExceedability() > 0.0f) {
            transform->set_position(potentialPosition);
        }
    }
}
