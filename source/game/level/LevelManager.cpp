#include "game/level/LevelManager.h"
#include "engine/core/Engine.h"
#include "engine/core/Input.h"
#include "game/core/Game.h"
#include "game/core/Tag.h"
#include "game/level/LevelGenerator.h"
#include "game/level/Tilemap.h"
#include "game/entity/HealthSystem.h"

void LevelManager::onAwake()
{
    //scripts
    levelGenerator = createComponent<LevelGenerator>();
}

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


    //player
    player = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!player) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: player is nullptr");
        return;
    }

    playerHS = player->getComponent<PlayerHealthSystem>(true);

    if (!playerHS) {
        VDebuger::print("<ERROR> :: LEVEL_MANAGER :: playerHS is nullptr");
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

void LevelManager::onUpdate(float dt)
{
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::P))
    {
        displayPauseScene(PauseSceneDataPack::Type::Pause);
    }

    if (playerHS && playerHS->getHealth() <= 0.0f)
    {
        displayPauseScene(PauseSceneDataPack::Type::Dead);
    }
}



int LevelManager::countKilldedEnemies() const
{
    int killedEnemies = 0;
    for (const auto& enemy : this->enemies)
    {
        if (!enemy)
        {
            ++killedEnemies;
            continue;
        }

        if (auto hs = enemy->getComponent<HealthSystem>(true))
        {
            if (hs->getHealth() <= 0.0f)
            {
                ++killedEnemies;
            }
        }
    }

    return killedEnemies;
}

bool LevelManager::isCompleted() const
{
    return enemies.size() == countKilldedEnemies();
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
    if (isCompleted())
    {
        isFinished = true;
        displayPauseScene(PauseSceneDataPack::Type::Completed);
    }
    else
    {
        notificationManager->message("Not ready!");
    }
}

void LevelManager::displayPauseScene(const PauseSceneDataPack::Type& type)
{
    PauseSceneDataPack::type = type;
    PauseSceneDataPack::killedEnemies = countKilldedEnemies();
    PauseSceneDataPack::allEnemies = enemies.size();
    PauseSceneDataPack::isCompleted = isCompleted() && isFinished;
    getGame()->changeScene(PAUSE_SCENE, true);
}

