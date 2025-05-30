#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <list>
#include <map>
#include <cmath>

class Collider;
class Scene;
struct Edges;

///
/// \brief Klasa realizujaca wykrywanie kolizji miedzy Colliderami.
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


    void init(Scene* scene, unsigned int chunkSize); //Ta metoda jest wywolywana przez silnik.
    void dispose(); //Ta metoda jest wywolywana przez silnik.


    void updateAll(); //Ta metoda jest wywolywana przez silnik.

    void updateChunks(Collider* collider); //Ta metoda jest wywolywana przez silnik.
    void removeFromOutdatedChunks(Collider* collider, Edges& colliderCurrentChunks); //Ta metoda jest wywolywana przez silnik.


    void updateCollisions(Collider* collider); //Ta metoda jest wywolywana przez silnik.
};

#endif // COLLISIONMANAGER_H
