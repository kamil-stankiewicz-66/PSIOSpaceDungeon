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

Collider::~Collider()
{
    if (!getGame()->get_currentScene())
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

                if (!other_object || !other_object->transform) {
                    continue;
                }

                if (!other_object->isEnable()) {
                    continue;
                }


                bool _result = checkCollision(other_collider, other_object->transform);

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
