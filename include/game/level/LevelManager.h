#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine/object/Object.h"
#include "game/player/PlayerCore.h"

class LevelGenerator;
class Tilemap;

///
/// \brief Level management class.
///

class LevelManager : public Object
{
public:

    //tilemaps
    Tilemap* tilemap = nullptr;
    Tilemap* fgTilemap = nullptr;
    Tilemap* bgTilemap = nullptr;

    //player
    PlayerCore* player = nullptr;

private:
    LevelGenerator* levelGenerator = nullptr;

    virtual void onStart() override;

    void loadLevel();
};

#endif // LEVELMANAGER_H
