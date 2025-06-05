#include "game/physics/Rigidbody.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"

void Rigidbody::onStart()
{
    tilemap = getGame()->get_currentScene()->findObject<Tilemap>("tilemap");

    if (!tilemap) {
        VDebuger::print("<ERROR> RIGIDBODY :: ON_START :: tilemap is nullptr");
    }
}

void Rigidbody::init(Transform* transform, Transform* rect)
{
    this->transform = transform;
    this->rect = rect;
}

void Rigidbody::addForce(const Vector2& force)
{
    if (!tilemap || !transform || !rect) {
        VDebuger::print("<ERROR> RIGIDBODY :: ADD_FORCE :: is not inited");
        return;
    }


    //friction value from tile

    float tileFactor = 1.0f;

    if (const Tile* tile = tilemap->getTileRealPos(rect->get_position().x, rect->get_position().y)) {
        tileFactor = tile->getExceedability();
    }


    //checking if rect would be in collision after moving

    Vector2 potentialPosition(rect->get_position() + (force * tileFactor));

    //if tile is nullptr, there is a collision
    if (auto tile = tilemap->getTileRealPos(potentialPosition.x, potentialPosition.y))
    {
        //move
        if (tile->getExceedability() > 0.0f) {
            transform->set_position(transform->get_position() + (force * tileFactor));
        }
    }
}
