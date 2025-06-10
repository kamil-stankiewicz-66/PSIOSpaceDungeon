#include "game/scenes/GameScene.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"
#include "game/level/LevelManager.h"
#include "game/level/Tilemap.h"
#include "game/player/PlayerCore.h"
#include "game/player/TrackingCamera.h"
#include "game/ui/Notification.h"

void GameScene::loadObjects()
{
    this->set_globalScale(2.0f);

    //camera
    {
        createObject<CameraHolder>();
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

    //ui
    {
        //health bar
        auto healthBar = getGame()->get_currentScene()->createObject<Slider>(2000u);
        healthBar->addTag(Tag::PLAYER_HEALTH_BAR.data());
        healthBar->init(true);
        healthBar->setFillColor(sf::Color::Red);
        healthBar->setBackgroundColor(sf::Color(23, 26, 33));
        healthBar->scaleWidth(0.5);
        healthBar->scaleHeight(0.7f);

        if (auto t = healthBar->getTransformPtr())
        {
            t->set_position(getGame()->get_window()->get_cornerPositions().leftUp);
            const auto& display = getGame()->get_window()->get_displaymode();
            t->add_position(0.08f * display.width, -0.05f * display.height);
        }

        //heal bar
        auto healBar = getGame()->get_currentScene()->createObject<Slider>(2000u);
        healBar->addTag(Tag::PLAYER_HEAL_BAR.data());
        healBar->init(true);
        healBar->setFillColor(sf::Color::Yellow);
        healBar->setBackgroundColor(sf::Color(23, 26, 33));
        healBar->scaleWidth(0.5);
        healBar->scaleHeight(0.1f);

        if (auto t = healBar->getTransformPtr())
        {
            t->set_position(getGame()->get_window()->get_cornerPositions().leftUp);
            const auto& display = getGame()->get_window()->get_displaymode();
            t->add_position(0.08f * display.width, (-0.05f * display.height) - healthBar->getHeight());
        }
    }

    //player
    {
        createObject<PlayerCore>(50);
    }

    //managers
    {
        auto notManager = createObject<NotificationManager>();
        notManager->getTransformPtr()->set_position(
            getGame()->get_window()->get_cornerPositions().rightUp - Vector2(0.0f, 0.2f * getGame()->get_window()->get_displaymode().height)
            );

        createObject<LevelManager>();
    }
}
