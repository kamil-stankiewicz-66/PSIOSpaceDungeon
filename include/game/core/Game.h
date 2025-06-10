#ifndef GAME_H
#define GAME_H

#include "engine/core/Engine.h"

//scene names
inline const std::string MAIN_SCENE = "main_scene";
inline const std::string GAME_SCENE = "game_scene";
inline const std::string STORE_SCENE = "store_scene";
inline const std::string PAUSE_SCENE = "pause_scene";

//game class
class Game : public Engine
{
private:
    bool m_isFullScreen = false;
    bool m_isFullScreenButtonPressed = false;

public:
    Game(string _title);
    ~Game();

    virtual void onUpdate(float dt) override;
};

#endif // GAME_H
