#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Scene.h"
#include "engine/object/Object.h"
#include "engine/object/Camera.h"
#include "engine/component/Collider.h"
#include "engine/core/Input.h"

class Entity : public GameObject
{
    Collider* m_collider = nullptr;
    Collider* player = nullptr;

    virtual void onStart() override {
        m_collider = this->getComponent<Collider>(true);
    }

    virtual void onUpdate(float dt) override
    {
        if (!player) {
            player = getGame()->get_currentScene()->findGameObject("Player")->getComponent<Collider>(true);
        }

        if (player && m_collider) {
            if (m_collider->isInCollisionWith(player)) {
                this->sprite->setColor(sf::Color::Red);
            }
            else {
                this->sprite->setColor(sf::Color::Green);
            }
        }

        this->transform->add_rotation(dt/10.f);
        this->transform->add_position(Vector2(dt/1000.f));
    }
};

class Player : public GameObject
{

    virtual void onStart() override {

    }

    virtual void onUpdate(float dt) override {
        auto _camera = this->getGame()->get_currentScene()->get_mainCamera();
        if (_camera) {
            if (auto _t = this->transform) {
                _t->set_position(_camera->transform->get_position() + (Input::Mouse::AXIS()*_camera->get_viewSize()));
            }
        }
    }
};

class BasicCamera : public Camera
{

};

class TestScene : public Scene
{
    void loadObjects() override
    {
        set_globalScale(0.002);

        auto _camera = createObject<BasicCamera>();
        _camera->set_viewSize(8.f);
        _camera->transform->set_position(Vector2());

        set_mainCamera(_camera);

        //test
        {
            {
                for (int i=-10; i<10; i++) {
                    for (int j=-10; j<10; j++) {
                        auto _go = createObject<Entity>();
                        _go->sprite->setTexture("test_textures\\6115912.jpg");
                        _go->transform->set_position(Vector2(i*1000,j*1000));
                        _go->transform->scaleBy(0.3f);
                        _go->transform->set_rotation(0);
                        auto _colider = _go->createComponent<BoxCollider>();
                        _colider->set(700.f, 700.f);
                        _go->addTag("entity");
                    }
                }
            }
            {
                auto _go = createObject<Player>();
                _go->sprite->setTexture("test_textures\\6115912.jpg");
                _go->transform->set_position(Vector2());
                _go->transform->scaleBy(0.3f);
                _go->transform->set_rotation(0);
                _go->sprite->setColor(sf::Color::Blue);
                auto _colider = _go->createComponent<BoxCollider>();
                _colider->set(700.f, 700.f);
                _go->addTag("Player");
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
        //_camera->set_rotation(_camera->get_rotation()-(dt/50.f));
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
