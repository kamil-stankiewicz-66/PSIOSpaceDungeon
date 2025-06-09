#include "game/level/LevelManager.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"
#include "game/level/LevelGenerator.h"
#include "game/level/Tilemap.h"

void LevelManager::onStart()
{
    this->addTag("LevelManager");

    if (!getGame()) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: game is nullptr");
        return;
    }


    //shortcut
    Scene* scene = getGame()->get_currentScene();

    if (!scene) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: scene is nullptr");
        return;
    }


    //tilemaps
    tilemap = scene->findObject<Tilemap>(Tag::TILEMAP.data());
    fgTilemap = scene->findObject<Tilemap>(Tag::TILEMAP_FG.data());
    bgTilemap = scene->findObject<Tilemap>(Tag::TILEMAP_BG.data());

    //check
    if (!tilemap || !fgTilemap || !bgTilemap) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: tilemap is nullptr");
        return;
    }


    //scripts
    levelGenerator = createComponent<LevelGenerator>();


    //player
    player = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!player) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: player is nullptr");
        return;
    }


    //notification manager
    notificationManager = getGame()->get_currentScene()->findObject<NotificationManager>();

    if (!notificationManager) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: notificationManager is nullptr");
        return;
    }


    //load
    loadLevel();


    //find all enemies
    enemies = getGame()->get_currentScene()->findObjects<Entity>(Tag::ENEMY.data(), true);
}

void LevelManager::loadLevel()
{
    //link
    Scene* scene = getGame()->get_currentScene();

    if (!scene) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: LOAD_LEVEL :: scene is nullptr");
        return;
    }


    //generate level
    levelGenerator->generate();
}

void LevelManager::finishLevel()
{
    bool flag(true);

    for (const auto& enemy : this->enemies)
    {
        if (!enemy) {
            continue;
        }

        //if health > 0 flag = false;
        flag = false;
    }

    //finish
    notificationManager->message("Not ready!");
}
