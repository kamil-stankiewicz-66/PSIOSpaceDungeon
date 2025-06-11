#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "engine/core/Engine.h"
#include "engine/core/CollisionManager.h"
#include "engine/core/VMath.h"







///
/// Collider
///


Edges::Edges(int x_min, int x_max, int y_min, int y_max)
{
    this->x_min = x_min;
    this->x_max = x_max;
    this->y_min = y_min;
    this->y_max = y_max;
}


bool Collider::init(Engine* engine, Object* object)
{
    if (!Component::init(engine, object)) {
        return false;
    }

    if (Scene* _scene = getGame()->get_currentScene())
    {
        auto& _collidersRegistry = getGame()->get_currentScene()->get_collisionManager()->collidersRegistry;

        if (std::find(_collidersRegistry.begin(), _collidersRegistry.end(), this) == _collidersRegistry.end())
        {
            _collidersRegistry.push_back(this);
        }

        return true;
    }

    return false;
}

Collider::Collider() : m_collisions() {}

Collider::~Collider()
{
    if (!getGame()->get_currentScene())
    {
        return;
    }

    if (!getGame()->isRunning())
    {
        return;
    }

    auto& _collidersRegistry = getGame()->get_currentScene()->get_collisionManager()->collidersRegistry;

    auto it = std::find(_collidersRegistry.begin(), _collidersRegistry.end(), this);

    if (it != _collidersRegistry.end())
    {
        _collidersRegistry.erase(it);
    }
}


void Collider::refreshCollisions()
{
    m_collisions.clear();

    for (int x = (this->chunks.x_min - m_chunksCheckingRange); x <= (this->chunks.x_max + m_chunksCheckingRange); x++)
    {
        for (int y = (this->chunks.y_min - m_chunksCheckingRange); y <= (this->chunks.y_max + m_chunksCheckingRange); y++)
        {
            auto& collidersInThisChunk = getGame()->get_currentScene()->get_collisionManager()->m_chunks[x][y];

            for (const auto& other_collider : collidersInThisChunk)
            {
                if (!other_collider || other_collider == this) {
                    continue;
                }


                Object* other_object = other_collider->getObject();

                if (!other_object || !other_object->getTransformPtr()) {
                    continue;
                }

                if (!other_object->isEnable()) {
                    continue;
                }


                bool _result = checkCollision(other_collider, other_object->getTransformPtr());

                if (_result)
                {
                    this->m_collisions.emplace(other_collider);
                    other_collider->m_collisions.emplace(this);
                }
                else
                {
                    auto it = other_collider->m_collisions.find(this);
                    if (it != other_collider->m_collisions.end()) {
                        other_collider->m_collisions.erase(it);
                    }
                }
            }

        }
    }
}



bool Collider::isInCollisionWith(Collider* other_collider) {
    return m_collisions.find(other_collider) != m_collisions.end();
}

const std::set<Collider*>& Collider::getCollisions() const {
    return m_collisions;
}







///
/// BoxCollider
///


void BoxCollider::set(float _x, float _y)
{
    if (_x > 0.0f) { this->x = _x; }
    if (_y > 0.0f) { this->y = _y; }

    this->updateEdges();
}


void BoxCollider::onUpdate(float _dt)
{
    if (getObject()->getTransformPtr()->inMove()) {
        this->updateEdges();
    }

    Collider::onUpdate(_dt);
}


//for this collider
bool BoxCollider::checkCollision(Collider* other_collider, Transform* other_transform)
{
    const Vector2 other_position = other_transform->get_position();
    const Vector2 nearestPointToOther = this->getNearestColliderPointTo(other_position, 0.0f);

    if (nearestPointToOther.x == other_position.x &&
        nearestPointToOther.y == other_position.y)
    {
        return true;
    }

    return other_collider->isThisPointInCollider(nearestPointToOther);
}

Vector2 BoxCollider::getNearestColliderPointTo(const Vector2& point, const float borderThickness)
{
    return Vector2(
        VMath::clamp(point.x, leftEdge + borderThickness, rightEdge - borderThickness),
        VMath::clamp(point.y, downEdge + borderThickness, upEdge - borderThickness)
        );
}


//for other collider
bool BoxCollider::isThisPointInCollider(const Vector2& point)
{
    if (this->x == 0.0f || this->y == 0.0f) {
        return false;
    }

    return
        VMath::isInRange(point.x, leftEdge, rightEdge) &&
        VMath::isInRange(point.y, downEdge, upEdge);
}


//getter
const float& BoxCollider::getSize_x() const {
    return this->x;
}

const float& BoxCollider::getSize_y() const {
    return this->y;
}


//for chunks
Edges BoxCollider::getEdges() const
{
    return Edges(
        (int)this->leftEdge, (int)this->rightEdge,
        (int)this->downEdge, (int)this->upEdge
        );
}


//helper
void BoxCollider::updateEdges()
{
    const Vector2 position = getObject()->getTransformPtr()->get_position();
    this->leftEdge = position.x - (this->x / 2.0f);
    this->rightEdge = position.x + (this->x / 2.0f);
    this->downEdge = position.y - (this->y / 2.0f);
    this->upEdge = position.y + (this->y / 2.0f);
}







///
/// CircleCollider
///


void CircleCollider::set(float _radius)
{
    if (_radius > 0.0f) {
        this->radius = _radius;
    }
}


//for this collider
bool CircleCollider::checkCollision(Collider* other_collider, Transform* other_transform)
{
    if (radius == 0.0f) {
        return false;
    }

    if (!other_collider)
    {
        VDebuger::print("<ERROR> CIRCLE_COLLIDER :: CHECK_COLLISION :: other_collider is nullptr");
        return false;
    }

    if (!other_transform)
    {
        VDebuger::print("<ERROR> CIRCLE_COLLIDER :: CHECK_COLLISION :: other_transform is nullptr");
        return false;
    }

    if (!getObject() || !getObject()->getTransformPtr())
    {
        VDebuger::print("<ERROR> CIRCLE_COLLIDER :: CHECK_COLLISION :: getObject() or getObject()->getTransformPtr() is nullptr");
        return false;
    }

    const Vector2 position = getObject()->getTransformPtr()->get_position();
    const Vector2 other_position = other_transform->get_position();

    if (position.distanceToLite(other_position) <= (radius * radius)) {
        return true;
    }

    return other_collider->isThisPointInCollider(getNearestColliderPointTo(other_position, 0.0f));
}

Vector2 CircleCollider::getNearestColliderPointTo(const Vector2& point, const float borderThickness)
{
    if (!getObject() || !getObject()->getTransformPtr())
    {
        VDebuger::print("<ERROR> CIRCLE_COLLIDER :: GET_NEAREST_COLLIDER_POINT_TO :: getObject() or getObject()->getTransformPtr() is nullptr");
        return false;
    }

    const Vector2& position = getObject()->getTransformPtr()->get_position();
    Vector2 angleVector = (point - position).get_normalized();
    return position + angleVector * (radius - borderThickness);
}


//for other collider
bool CircleCollider::isThisPointInCollider(const Vector2& _point)
{
    if (radius == 0.0f) {
        return false;
    }

    if (!getObject()) {
        return false;
    }

    if (Transform* _transform = getObject()->getTransformPtr()) {
        return _transform->get_position().distanceToLite(_point) <= (radius * radius);
    }

    return false;
}


//getter
const float& CircleCollider::getRadius() const {
    return radius;
}


//for chunks
Edges CircleCollider::getEdges() const
{
    if (!getObject() || !getObject()->getTransformPtr()) {
        return Edges();
    }

    const Vector2& position = getObject()->getTransformPtr()->get_position();

    return Edges(
        (int)(position.x - radius),
        (int)(position.x + radius),
        (int)(position.y - radius),
        (int)(position.y + radius)
        );
}
