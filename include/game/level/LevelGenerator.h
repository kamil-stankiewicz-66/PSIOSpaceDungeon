#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "engine/component/Component.h"
#include "engine/core/Vector2.h"
#include <random>

using namespace std;
using tilePos = pair<int,int>;

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
    float getRndFloat(const float& min, const float& max);
    float getDistanceInTiles(const tilePos& p1, const tilePos& p2);

private:
    virtual void onAwake() override;

    //main
    void generate();

    //tiles generators
    void generateCorridors();
    void generateCorridor(int& x, int& y);
    void generateRoom(int& x, int& y);
    void generateWalls();

    //other generators
    vector<Vector2> getRealRndPositionsInRoom(const tilePos& leftDown, const tilePos& rightTop,
                                              const int& number, const int& minDistance, const int& maxAttemptsNum);
    void generateChestsInRoom(const tilePos& leftDown, const tilePos& rightTop);
    void generateEntitiesInRoom(const tilePos& leftDown, const tilePos& rightTop);

    //entity creator
    static Entity* createEntity(Scene* scene, const EntityData& data,
                                uint renderLayer = 0u, Object* parent = nullptr);
};

#endif // LEVELGENERATOR_H
