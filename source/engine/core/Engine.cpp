#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"
#include "engine/core/Input.h"



///
/// corners positions
///

void VWindow::CornerPositions::init(const sf::VideoMode& displayMode)
{
    float _h_half = (float)displayMode.height / 2.0f;
    float _w_half = (float)displayMode.width / 2.0f;
    leftUp = Vector2(-_w_half, _h_half);
    rightUp = Vector2(_w_half, _h_half);
    leftDown = Vector2(-_w_half, -_h_half);
    rightDown = Vector2(_w_half, -_h_half);
}



///
/// window
///

VWindow::VWindow() : sfwindow(nullptr), displayMode()
{}

VWindow::~VWindow()
{
    if (this->sfwindow) {
        sfwindow->close();
        sfwindow = nullptr;
    }

    VDebuger::print("WINDOW :: DESTRUCTOR :: cleared");
}


bool VWindow::init(const string WINDOW_TITLE)
{
    //display mode
    this->displayMode = sf::VideoMode::getDesktopMode();

    //window
    this->sfwindow = make_unique<sf::RenderWindow>(this->displayMode, WINDOW_TITLE, sf::Style::Close);
    this->sfwindow->clear(this->m_background);;

    //corner positions
    this->cornerPositions.init(this->displayMode);

    //result
    return this->isInited();
}


void VWindow::clear()
{
    this->sfwindow->clear(this->m_background);
}


bool VWindow::isInited() const
{
    return this->sfwindow.get() && this->sfwindow->isOpen();
}


sf::RenderWindow* VWindow::get_renderwindow() const {
    return this->sfwindow.get();
}

const sf::VideoMode& VWindow::get_displaymode() const {
    return this->displayMode;
}

const VWindow::CornerPositions& VWindow::get_cornerPositions() const {
    return this->cornerPositions;
}

const sf::Color& VWindow::get_BGColor() const {
    return this->m_background;
}


void VWindow::set_BGColor(const sf::Color& _bgcolor) {
    this->m_background = _bgcolor;
}

















///
/// Engine
///



Engine::Engine(const string WINDOW_TITLE) : currentScene(nullptr), m_isRunning(false)
{    
    VDebuger::print("ENGINE :: INIT");

    //window
    window = make_unique<VWindow>();
    if (!window->init(WINDOW_TITLE))
    {
        VDebuger::print("<ERROR> ENGINE :: WINDOW INIT ERROR");
    }

    //miejsce na init dla input
}

Engine::~Engine()
{
    window = nullptr;

    VDebuger::print("ENGINE :: DESTRUCTOR :: cleared");
}




///
/// protected
///

void Engine::onUpdate(float deltaTime) {}




///
/// gameloop
///

int Engine::run(const unsigned int MAX_FPS)
{
    if (!this->window || !this->window->isInited())
    {
        VDebuger::print("<ERROR> ENGINE :: YOU HAVE TO INIT THE WINDOW !!!");
        return -1;
    }

    //vars for loop
    const float FRAME_DURATION = 1000.0f / MAX_FPS;
    bool m_init_iteration = true;
    sf::Clock clock;
    float elapsed;
    float deltaTime = 0.f;

    //main loop
    this->m_isRunning = true;
    while (this->m_isRunning)
    {
        //event handling
        sf::Event event;
        while (this->window->get_renderwindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                this->m_isRunning = false;
            }
        }

        if (!window || !window->isInited()) {
            m_isRunning = false;
        }

        //set
        deltaTime = m_init_iteration ? (FRAME_DURATION)
                                     : (clock.restart().asMilliseconds());

        //clear window
        window->clear();

        //miejsce na update input

        //update silnika
        this->taskHandling();
        this->onUpdate(deltaTime);

        //update sceny
        if (this->currentScene)
        {
            this->currentScene->update(deltaTime);
        }

        //display
        window->get_renderwindow()->display();

        //wait
        elapsed = clock.getElapsedTime().asMilliseconds();
        if (elapsed < FRAME_DURATION)
        {
            sf::sleep(sf::milliseconds(FRAME_DURATION - elapsed));
        }

        //end init iteration
        if (m_init_iteration)
            m_init_iteration = false;
    }

    return 0;
}

void Engine::shutdown()
{
    m_isRunning = false;
}

void Engine::taskHandling()
{
    //scene changer
    if (this->sceneLoadData.isInited())
    {
        this->loadScene();
        this->sceneLoadData.dispose();
    }
}





///
/// getters
///

VWindow* Engine::get_window() const
{
    return this->window.get();
}

Scene* Engine::get_currentScene() const {
    return currentScene;
}




///
/// scene manager
///


void Engine::SceneLoadData::set(string _name, bool _keepChanges) {
    this->name = _name;
    this->keepChanges = _keepChanges;
}

void Engine::SceneLoadData::dispose() {
    this->name = string();
    this->keepChanges = bool(false);
}

bool Engine::SceneLoadData::isInited() {
    return this->name != string();
}

const string& Engine::SceneLoadData::getName() const {
    return this->name;
}

const bool& Engine::SceneLoadData::getKeepChanges() const {
    return this->keepChanges;
}


void Engine::changeScene(const string _name, bool _keepChanges)
{
    if (this->sceneLoadData.isInited())
    {
        VDebuger::print("ENGINE :: CHANGE_SCENE :: Task is overflowing. Cannot load scene:", _name);

        return;
    }

    if (this->scenes.find(_name) == this->scenes.end())
    {
        VDebuger::print("ENGINE :: CHANGE_SCENE :: There is no scene called:", _name);

        return;
    }

    if (this->currentScene &&
        _name == this->currentScene->get_name())
    {
        VDebuger::print("ENGINE :: CHANGE_SCENE :: This scene [ name =", _name, "] is already loaded. To reload, call Scene::reload()");

        return;
    }

    //set
    this->sceneLoadData.set(_name, _keepChanges);
}


void Engine::loadScene()
{
    //log
    VDebuger::print("ENGINE :: TASK_HANDLING :: SCENE_CHANGER :: SCENE_LOADER :: setting current scene to", this->sceneLoadData.getName(), "started");

    if (this->currentScene &&
        !this->sceneLoadData.getKeepChanges())
    {
        this->currentScene->dispose();
    }

    this->currentScene = this->scenes[this->sceneLoadData.getName()].get();

    if (this->currentScene->isEmpty())
    {
        //load and start()
        this->currentScene->load();
    }
    else
    {
        //only start()
        VDebuger::print("start()");
    }

    //log
    VDebuger::print("ENGINE :: TASK_HANDLING :: SCENE_CHANGER :: SCENE_LOADER :: set current scene to", this->sceneLoadData.getName(), "completed");
}
