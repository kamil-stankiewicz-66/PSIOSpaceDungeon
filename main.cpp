#include "engine/core/Engine.h"
#include <iostream>

class Game : public Engine
{
public:
    Game(string _name) : Engine(_name)
    {
        std::cout << "Game()" <<std::endl;
        this->get_window()->set_BGColor(sf::Color::Green);
    }

    bool _flag = false;
    virtual void onUpdate(float dt) override
    {
        if (_flag){
            std::cout << "dt =" << dt << std::endl;
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
