#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Scene.h"
#include "engine/object/Object.h"

class Entity : public GameObject
{
    virtual void onUpdate(float dt) override{
        this->transform->add_rotation(dt/4.);
        //cout << this->transform->get_rotation() << endl;
    }
};

class TestScene : public Scene
{
    void loadObjects() override
    {
        set_globalScale(0.001);

        //test
        {
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(Vector2());
                _go->transform->scaleBy(0.3f);
                _go->transform->set_rotation(0);
                _go->sprite->setColor(sf::Color::Red);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().leftUp);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().rightUp);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().rightDown);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().leftDown);
                _go->transform->set_rotation(0);
            }
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
    }

};

int main()
{
    Game game("Test");
    game.run();
    return 0;
}
