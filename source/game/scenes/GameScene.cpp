#include "game/scenes/GameScene.h"
#include "game/core/Parameter.h"
#include "game/core/Tag.h"
#include "game/entity/BasicEntity.h"
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

    //tilemaps
    {
        const float cellSize = 16.0f;
        const float scale = 1.75f * get_globalScale();

        auto tilemap = createObject<Tilemap>(20);
        tilemap->addTag(Tag::TILEMAP.data());
        tilemap->setData(cellSize, scale);

        auto bgtilemap = createObject<Tilemap>(10);
        bgtilemap->addTag(Tag::TILEMAP_BG.data());
        bgtilemap->setData(cellSize, scale);

        auto fgtilemap = createObject<Tilemap>(30);
        fgtilemap->addTag(Tag::TILEMAP_FG.data());
        fgtilemap->setData(cellSize, scale);
    }

    //player
    {
        createObject<PlayerCore>(50);
    }

    //managers
    {
        createObject<LevelManager>();
    }

    //test entity
    {
        auto e = createObject<BasicEntity>(200);
        e->getSpritePtr()->setTexture(Asset::Graphics::ORC_ARMORED.data());
        e->getTransformPtr()->scaleBy(2.0f);
    }
}
