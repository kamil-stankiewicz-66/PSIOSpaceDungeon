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


bool VWindow::init(const string WINDOW_TITLE, const bool fullscreen)
{
    //display mode
    this->displayMode = sf::VideoMode::getDesktopMode();

    //vars
    this->m_windowTitle = WINDOW_TITLE;
    this->m_isFullscreen = fullscreen;

    //window
    this->makeWindow();

    //corner positions
    this->cornerPositions.init(this->displayMode);

    //result
    return this->isInited();
}

bool VWindow::makeWindow()
{
    this->sfwindow = nullptr;
    this->sfwindow = make_unique<sf::RenderWindow>(this->displayMode, m_windowTitle, m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Close);
    this->clear();

    //result
    return this->isInited();
}

void VWindow::setFullscreen(const bool fullscreen)
{
    if(m_isFullscreen == fullscreen) {
        return;
    }

    m_isFullscreen = fullscreen;
    makeWindow();
}


void VWindow::clear()
{
    this->sfwindow->clear(this->m_background);
}


bool VWindow::isInited() const
{
    bool flag = this->sfwindow.get() && this->sfwindow->isOpen();

    if (!flag) {
        VDebuger::print("<ERROR> :: VWindow :: IS_INITED :: WINDOW INIT ERROR");
    }

    return flag;
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


void VWindow::setBGColor(const sf::Color& _bgcolor) {
    this->m_background = _bgcolor;
}









///
/// Engine
///


Engine::Engine(const string WINDOW_TITLE, const bool fullscreen) : currentScene(nullptr), m_isRunning(false)
{    
    VDebuger::print("ENGINE :: INIT");

    //window
    window = make_unique<VWindow>();
    if (!window->init(WINDOW_TITLE, fullscreen))
    {
        VDebuger::print("<ERROR> ENGINE :: WINDOW INIT ERROR");
    }

    //input init
    Input::init(window->get_renderwindow());
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

        //engine update
        Input::update();
        this->taskHandling();
        this->onUpdate(deltaTime);

        //scene update
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

Scene* Engine::get_scene(const string& _name) const
{
    auto it = this->scenes.find(_name);

    if (it != this->scenes.end())
    {
        return it->second.get();
    }

    return nullptr;
}

bool Engine::isRunning() const {
    return m_isRunning;
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

    //log
    VDebuger::print("ENGINE :: TASK_HANDLING :: SCENE_CHANGER :: SCENE_LOADER :: set current scene to", this->sceneLoadData.getName(), "completed");
}
