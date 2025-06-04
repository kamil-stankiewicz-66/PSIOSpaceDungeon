#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine/object/Object.h"

class LevelGenerator;
class Tilemap;

///
/// \brief Level management class.
///

class LevelManager : public Object
{
public:
    Tilemap* tilemap;
    Tilemap* fgTilemap;
    Tilemap* bgTilemap;

private:
    LevelGenerator* levelGenerator;

    virtual void onStart() override;

    void loadLevel();
};

#endif // LEVELMANAGER_H
