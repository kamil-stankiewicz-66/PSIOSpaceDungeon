#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "engine/core/Input.h"

class Entity : public GameObject
{
    virtual void onUpdate(float dt) override{
        std::cout << "update" << endl;
    }
};

class TestScene : public Scene
{
    void loadObjects() override
    {
        //test
        {
            auto o = createObject<Entity>();
            o->addTag("obiekt1");
        }
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

        //obsluga klawiszy (zmiana koloru tla) b-niebieski, r-czerwony

        if (Input::Keyboard::isPressed(Input::Keyboard::B)) {
            get_window()->set_BGColor(sf::Color::Blue);
        }
        else if (Input::Keyboard::isPressed(Input::Keyboard::R)) {
            get_window()->set_BGColor(sf::Color::Red);
        }

        if (Input::Mouse::LEFT_BUTTON()) {
            VDebuger::print(Input::Mouse::AXIS());
        }
    }

};

int main()
{
    Game game("Test");
    game.run();
    return 0;
}
