#include "game/core/Game.h"
#include "engine/core/Input.h"
#include "game/scenes/MainScene.h"
#include "game/scenes/GameScene.h"

Game::Game(string _title) : Engine(_title)
{
    //create scenes
    this->createScene<MainScene>(MAIN_SCENE);
    this->createScene<GameScene>(GAME_SCENE);

    //load main scene
    this->changeScene(MAIN_SCENE);
}

void Game::onUpdate(float deltatime)
{
    //exit
    if (Input::Keyboard::isPressed(Input::Keyboard::Escape)) {
        this->shutdown();
    }
}
