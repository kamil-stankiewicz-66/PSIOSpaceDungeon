#include "engine/core/CollisionManager.h"
#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include <algorithm>

void CollisionManager::init(Scene* _scene, unsigned int _chunksSize)
{
    this->m_scene = _scene;
    this->m_chunkSize = _chunksSize;
}

void CollisionManager::dispose()
{
    this->m_chunks.clear();
}

void CollisionManager::updateAll()
{
    for (auto& collider : collidersRegistry)
    {
        if (!collider || !collider->getObject() || !collider->getObject()->transform) {
            continue;
        }

        //if not enable - delate from all chunks
        if (!collider->getObject()->isEnable())
        {
            if (collider->getObject()->getState() == ObjectState::Undead)
            {
                removeFromOutdatedChunks(collider, collider->chunks);
            }

            continue;
        }

        //if reborn - refresh
        if (!collider->getObject()->transform->inMove() &&
            collider->getObject()->getState() != ObjectState::Reborn)
        {
            continue;
        }

        //update all
        updateChunks(collider);
        updateCollisions(collider);
    }

}

void CollisionManager::updateChunks(Collider* collider)
{
    Edges& colliderCurrentChunks = collider->chunks;
    Edges colliderEdges = collider->getEdges();

    int chunk_x_min = colliderEdges.x_min / m_chunkSize;
    int chunk_x_max = colliderEdges.x_max / m_chunkSize;
    int chunk_y_min = colliderEdges.y_min / m_chunkSize;
    int chunk_y_max = colliderEdges.y_max / m_chunkSize;


    //skip if not changed
    if (colliderCurrentChunks.x_min == chunk_x_min &&
        colliderCurrentChunks.x_max == chunk_x_max &&
        colliderCurrentChunks.y_min == chunk_y_min &&
        colliderCurrentChunks.y_max == chunk_y_max &&
        collider->getObject()->getState() == ObjectState::Normal)
    {
        return;
    }


    //remove from outdated chunks
    removeFromOutdatedChunks(collider, colliderCurrentChunks);


    //add to current chunks
    for (int chunk_x = chunk_x_min; chunk_x <= chunk_x_max; chunk_x++)
    {
        for (int chunk_y = chunk_y_min; chunk_y <= chunk_y_max; chunk_y++)
        {
            list<Collider*>& collidersInChunk = m_chunks[chunk_x][chunk_y];

            auto it = find(collidersInChunk.begin(), collidersInChunk.end(), collider);
            if (it == collidersInChunk.end())
            {
                collidersInChunk.push_back(collider);
            }
        }
    }


    //refresh in collider
    colliderCurrentChunks.x_min = chunk_x_min;
    colliderCurrentChunks.x_max = chunk_x_max;
    colliderCurrentChunks.y_min = chunk_y_min;
    colliderCurrentChunks.y_max = chunk_y_max;
}

void CollisionManager::removeFromOutdatedChunks(Collider* collider, Edges& colliderCurrentChunks)
{
    for (int chunk_x = colliderCurrentChunks.x_min; chunk_x <= colliderCurrentChunks.x_max; chunk_x++)
    {
        for (int chunk_y = colliderCurrentChunks.y_min; chunk_y <= colliderCurrentChunks.y_max; chunk_y++)
        {
            list<Collider*>& collidersInChunk = m_chunks[chunk_x][chunk_y];

            auto it = find(collidersInChunk.begin(), collidersInChunk.end(), collider);
            if (it != collidersInChunk.end())
            {
                collidersInChunk.erase(it);
            }
        }
    }
}


void CollisionManager::updateCollisions(Collider* collider)
{
    collider->refreshCollisions();
}
