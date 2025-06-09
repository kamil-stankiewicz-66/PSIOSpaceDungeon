#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine/object/Object.h"
#include "game/player/PlayerCore.h"
#include "game/ui/Notification.h"

class LevelGenerator;
class Tilemap;

///
/// \brief Level management class.
///

class LevelManager : public Object
{
    friend class LevelGenerator;
    friend class FinishPoint; //for call finish level

public:

    //tilemaps
    Tilemap* tilemap = nullptr;
    Tilemap* fgTilemap = nullptr;
    Tilemap* bgTilemap = nullptr;

    //link
    PlayerCore* player = nullptr;
    NotificationManager* notificationManager = nullptr;

    //entities
    vector<Entity*> enemies;

private:
    LevelGenerator* levelGenerator = nullptr;

    //engine
    virtual void onStart() override;

    //actions
    void loadLevel();
    void finishLevel();
};

#endif // LEVELMANAGER_H
