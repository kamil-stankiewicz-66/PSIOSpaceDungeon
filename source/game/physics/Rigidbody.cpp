#include "game/physics/Rigidbody.h"
#include "engine/core/Engine.h"
#include "engine/object/Object.h"
#include "game/core/Tag.h"

void Rigidbody::onStart()
{
    tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());

    if (!tilemap) {
        VDebuger::print("<ERROR> RIGIDBODY :: ON_START :: tilemap is nullptr");
    }
}

bool Rigidbody::isNull() const {
    return !tilemap || !transform || !rect;
}

void Rigidbody::init(Transform* transform, Transform* rect)
{
    this->transform = transform;
    this->rect = rect;
}

void Rigidbody::addForce(const Vector2& force)
{
    if (this->isNull())
    {
        tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());

        if (this->isNull()) {
            VDebuger::print("<ERROR> RIGIDBODY :: ON_START :: tilemap is nullptr");
            return;
        }
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
        if (tile->getExceedability() > 0.0f)
        {
            transform->set_position(transform->get_position() + (force * tileFactor));
            return;
        }
    }


    //try slide

    //if tile is nullptr, there is a collision
    if (auto tile = tilemap->getTileRealPos(potentialPosition.x, rect->get_position().y))
    {
        //move
        if (tile->getExceedability() > 0.0f)
        {
            transform->set_position(transform->get_position().x + (force.x * tileFactor), transform->get_position().y);
            return;
        }
    }

    //if tile is nullptr, there is a collision
    if (auto tile = tilemap->getTileRealPos(rect->get_position().x, potentialPosition.y))
    {
        //move
        if (tile->getExceedability() > 0.0f)
        {
            transform->set_position(transform->get_position().x, transform->get_position().y + (force.y * tileFactor));
            return;
        }
    }
}
