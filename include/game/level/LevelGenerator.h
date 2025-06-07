#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "engine/component/Component.h"
#include <random>

using namespace std;

class LevelManager;
class Entity;
class Scene;
struct EntityData;

///
/// \brief Generates a dungeon-style level.
///

class LevelGenerator : public Component
{
    friend class LevelManager;
    LevelManager* levelManager;

    //calculation
    std::mt19937 gen;
    int m_direction;
    int m_room_size_x;
    int m_room_size_y;

    int getRndInt(const int& min, const int& max);

private:
    virtual void onAwake() override;

    //main
    void generate();

    //helpers
    void generateCorridors();
    void generateCorridor(int& x, int& y);
    void generateRoom(int& x, int& y);
    void generateWalls();


    //entity creator
    static Entity* createEntity(Scene* scene, const EntityData& data,
                                uint renderLayer = 0u, Object* parent = nullptr);
};

#endif // LEVELGENERATOR_H
