#include "game/level/LevelManager.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"
#include "game/level/LevelGenerator.h"
#include "game/level/Tilemap.h"

void LevelManager::onStart()
{
    //shortcut
    Scene* scene = getGame()->get_currentScene();

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


    //load
    loadLevel();
}

void LevelManager::loadLevel()
{
    //link
    Scene* scene = getGame()->get_currentScene();

    if (!scene) {
        return;
    }


    //generate level
    levelGenerator->generate();

}
