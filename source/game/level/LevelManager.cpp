#include "game/level/LevelManager.h"
#include "engine/core/Engine.h"
#include "game/level/LevelGenerator.h"
#include "game/level/Tilemap.h"

void LevelManager::onStart()
{
    //shortcut
    Scene* scene = getGame()->get_currentScene();

    //tilemaps
    tilemap = scene->findObject<Tilemap>("tilemap");
    fgTilemap = scene->findObject<Tilemap>("fg_tilemap");
    bgTilemap = scene->findObject<Tilemap>("bg_tilemap");

    //check
    if (!tilemap || !fgTilemap || !bgTilemap) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: tilemap is nullptr");
        return;
    }

    //scripts
    levelGenerator = createComponent<LevelGenerator>();

    //load
    loadLevel();
}

void LevelManager::loadLevel()
{
    //generate level
    levelGenerator->generate();
}
