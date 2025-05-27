#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"

class Game : public Engine
{
public:
    Game(string _name) : Engine(_name)
    {
        VDebuger::print("Game()");
        this->get_window()->set_BGColor(sf::Color::Green);
    }

    bool _flag = false;
    virtual void onUpdate(float dt) override
    {
        if (_flag){
            VDebuger::print("dt =", dt);
        }
        _flag = !_flag;
    }

};

int main()
{
    Game game("Test");
    game.run();
    return 0;
}
