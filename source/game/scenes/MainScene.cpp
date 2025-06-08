#include "game/scenes/MainScene.h"
#include "game/ui/BasicButtons.h"
#include "game/core/Game.h"

void MainScene::loadObjects()
{
    set_globalScale(1.f);

    {
        auto play_button = createObject<MenuButton>();
        play_button->setText("Play");

        play_button->addListener([this](){
            this->getGame()->changeScene(GAME_SCENE);
        });


        auto store_button = createObject<MenuButton>();
        store_button->setText("Store");

        store_button->addListener([this](){
            this->getGame()->changeScene(STORE_SCENE);
        });


        vector<MenuButton*> buttons {store_button, play_button};
        int space = getGame()->get_window()->get_displaymode().width / (buttons.size() + 1);
        Vector2 leftDown = getGame()->get_window()->get_cornerPositions().leftDown;
        leftDown.y += getGame()->get_window()->get_displaymode().height /10;

        for (int i = 0; i < buttons.size(); ++i)
        {
            buttons[i]->getTransformPtr()->set_position(leftDown + Vector2(space*(i+1)));
        }
    }
}
