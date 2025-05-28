#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Scene.h"

class TestScene : public Scene
{
public:
    TestScene()
    {
        VDebuger::print("TEST_SCENE");
    }
};

class Game : public Engine
{
public:
    Game(string _name) : Engine(_name)
    {
        createScene<TestScene>("test_scene");
        this->changeScene("test_scene");
    }

    bool _flag = false;
    virtual void onUpdate(float dt) override
    {
        //VDebuger::print("deltatime =", dt);
        //get_window()->set_BGColor(sf::Color::Blue);

        if (_flag){
            //VDebuger::print("dt =", dt);
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
