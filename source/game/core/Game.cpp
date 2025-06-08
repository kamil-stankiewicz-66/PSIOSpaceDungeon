#include "game/core/Game.h"
#include "engine/core/Input.h"
#include "game/core/Parameter.h"
#include "game/core/ScriptableObject.h"
#include "game/scenes/MainScene.h"
#include "game/scenes/GameScene.h"

Game::Game(string _title) : Engine(_title, false)
{
    //background color
    this->get_window()->setBGColor(sf::Color(12, 21, 36));

    //init
    Parameters::init();
    WeaponSO::init();
    EntitySO::init();

    //create scenes
    this->createScene<MainScene>(MAIN_SCENE);
    this->createScene<GameScene>(GAME_SCENE);

    //load main scene
    this->changeScene(MAIN_SCENE);
}

void Game::onUpdate(float deltatime)
{
    //exit
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::Escape))
    {
        if(!m_isFullScreenButtonPressed)
        {
            m_isFullScreenButtonPressed = true;
            m_isFullScreen = !m_isFullScreen;
            this->get_window()->setFullscreen(m_isFullScreen);
        }
    }
    else
    {
        m_isFullScreenButtonPressed = false;
    }

    cout<< m_isFullScreen << " " << m_isFullScreenButtonPressed <<endl;
}
