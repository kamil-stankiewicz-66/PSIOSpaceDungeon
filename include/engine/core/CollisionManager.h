#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <list>
#include <map>
#include <cmath>

class Collider;
class Scene;
struct Edges;

///
/// \brief Class that handles collision detection between Colliders.
///

class CollisionManager
{
    friend class Collider;
    friend class Scene;

private:
    Scene* m_scene;
    int m_chunkSize;

    std::list<Collider*> collidersRegistry;
    std::map<int, std::map<int, std::list<Collider*>>> m_chunks; //chunks[x][y]


    void init(Scene* scene, unsigned int chunkSize); //This method is called by the engine.
    void dispose(); //This method is called by the engine.


    void updateAll(); //This method is called by the engine.

    void updateChunks(Collider* collider); //This method is called by the engine.
    void removeFromOutdatedChunks(Collider* collider, Edges& colliderCurrentChunks); //This method is called by the engine.


    void updateCollisions(Collider* collider); //This method is called by the engine.
};

#endif // COLLISIONMANAGER_H
