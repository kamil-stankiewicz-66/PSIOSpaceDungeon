#include "game/scenes/GameScene.h"
#include "game/player/PlayerCore.h"

void GameScene::loadObjects()
{
    this->set_globalScale(2.0f);

    createObject<PlayerCore>(50);
}
