#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "engine/object/Camera.h"

class Entity : public GameObject
{
    virtual void onUpdate(float dt) override{
        this->transform->add_rotation(dt/4.);
        //cout << this->transform->get_rotation() << endl;
    }
};

class BasicCamera : public Camera
{

};

class TestScene : public Scene
{
    void loadObjects() override
    {
        set_globalScale(0.001);

        auto _camera = createObject<BasicCamera>();
        _camera->set_viewSize(8.f);
        _camera->transform->set_position(Vector2(3000.f));

        set_mainCamera(_camera);

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
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().leftUp *3.f);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().rightUp *3.f);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().rightDown *3.f);
                _go->transform->set_rotation(0);
            }
            {
                auto _go = createObject<Entity>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(this->getGame()->get_window()->get_cornerPositions().leftDown *3.f);
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

    Camera* _camera = nullptr;
    bool _flag = false;
    virtual void onUpdate(float dt) override
    {
        //VDebuger::print("deltatime =", dt);
        //get_window()->set_BGColor(sf::Color::Blue);

        if (!_camera){
            _camera = this->get_currentScene()->get_mainCamera();
        }

        //_camera->set_viewSize(_camera->get_viewSize()-(dt*0.001f));
        //_camera->transform->add_position(Vector2(dt));
        _camera->set_rotation(_camera->get_rotation()-(dt/50.f));
        //VDebuger::print(_camera->get_rotation());

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
