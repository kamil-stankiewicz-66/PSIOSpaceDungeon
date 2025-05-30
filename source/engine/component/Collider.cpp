#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "engine/core/Engine.h"
#include "engine/core/CollisionManager.h"


Edges::Edges(int x_min, int x_max, int y_min, int y_max)
{
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
}


bool Collider::init(Engine* engine, Object* object)
{
    return false;
}

Collider::~Collider()
{

}


void Collider::refreshCollisions()
{

}



bool Collider::isInCollisionWith(Collider* other_collider) {
    return m_collisions.find(other_collider) != m_collisions.end();
}

const std::set<Collider*>& Collider::getCollisions() const {
    return m_collisions;
}
