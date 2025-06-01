#include "game/scenes/MainScene.h"
#include "game/ui/BasicButtons.h"
#include "game/core/Asset.h"
#include "game/core/Game.h"

void MainScene::loadObjects()
{
    set_globalScale(0.01f);

    {
        auto play_button = createObject<MenuButton>();

        play_button->addListener([this](){
            this->getGame()->changeScene(GAME_SCENE);
        });
    }
}
