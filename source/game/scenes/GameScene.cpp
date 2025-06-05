#include "game/scenes/GameScene.h"
#include "game/core/Parameter.h"
#include "game/level/LevelManager.h"
#include "game/level/Tilemap.h"
#include "game/player/PlayerCore.h"
#include "game/player/TrackingCamera.h"

void GameScene::loadObjects()
{
    this->set_globalScale(2.0f);

    //camera
    {
        auto cam = createObject<TrackingCamera>();
        cam->set_viewSize(Parameters::get_camera_viewSize());
        set_mainCamera(cam);
    }

    //managers
    {
        createObject<LevelManager>();
    }

    //player
    {
        createObject<PlayerCore>(50);
    }

    //tilemaps
    {
        const float cellSize = 16.0f;
        const float scale = 2.5f * get_globalScale();

        auto tilemap = createObject<Tilemap>(20);
        tilemap->addTag("tilemap");
        tilemap->setData(cellSize, scale);

        auto bgtilemap = createObject<Tilemap>(10);
        bgtilemap->addTag("bg_tilemap");
        bgtilemap->setData(cellSize, scale);

        auto fgtilemap = createObject<Tilemap>(30);
        fgtilemap->addTag("fg_tilemap");
        fgtilemap->setData(cellSize, scale);
    }
}
