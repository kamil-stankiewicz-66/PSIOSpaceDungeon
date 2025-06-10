#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "engine/object/Object.h"
#include "game/player/PlayerCore.h"
#include "game/ui/Notification.h"
#include "game/scenes/PauseScene.h"

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
    PlayerHealthSystem* playerHS = nullptr;
    NotificationManager* notificationManager = nullptr;

    //entities
    vector<Entity*> enemies;

    //info
    int countKilldedEnemies() const;
    bool isCompleted() const;

private:
    LevelGenerator* levelGenerator = nullptr;

    //flag
    bool isFinished;

    //engine
    virtual void onAwake() override;
    virtual void onStart() override;
    virtual void onUpdate(float) override;

    //actions
    void loadLevel();
    void finishLevel();

    //set scene
    void displayPauseScene(const PauseSceneDataPack::Type&);
};

#endif // LEVELMANAGER_H
