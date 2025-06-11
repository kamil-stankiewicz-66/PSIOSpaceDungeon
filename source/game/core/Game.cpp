#include "game/core/Game.h"
#include "engine/core/Input.h"
#include "game/core/DataBlock.h"
#include "game/core/Parameter.h"
#include "game/core/ScriptableObject.h"
#include "game/core/Serializer.h"
#include "game/scenes/MainScene.h"
#include "game/scenes/GameScene.h"
#include "game/scenes/StoreScene.h"
#include "game/scenes/PauseScene.h"


Game::Game(string _title) : Engine(_title, false)
{
    //background color
    this->get_window()->setBGColor(sf::Color(12, 21, 36));

    //load player data
    SPlayerData data;
    Serializer::deserializeFromFile(data, FilePath::PLAYER_DATA.data());
    PlayerData::setExpPoints(data.exp_points);
    PlayerData::setWeaponID(data.weapon_id);
    PlayerData::setCoins(data.coins);

    //init
    Parameters::init();
    WeaponSO::init();
    EntitySO::init();

    //create scenes
    this->createScene<MainScene>(MAIN_SCENE);
    this->createScene<GameScene>(GAME_SCENE);
    this->createScene<StoreScene>(STORE_SCENE);
    this->createScene<PauseScene>(PAUSE_SCENE);

    //load main scene
    this->changeScene(MAIN_SCENE);
}

Game::~Game()
{
    //save player data
    SPlayerData data;
    data.exp_points = PlayerData::getExpPoints();
    data.weapon_id = PlayerData::getWeaponID();
    data.coins = PlayerData::getCoins();
    Serializer::serializeToFile(data, FilePath::PLAYER_DATA.data());
}

void Game::onUpdate(float deltatime)
{
    //exit
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::Escape))
    {
        if(!m_isFullScreenButtonPressed && this->get_window())
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
}
