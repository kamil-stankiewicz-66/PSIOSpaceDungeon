#include "engine/core/Engine.h"
#include "engine/core/Debuger.h"




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
    this->sfwindow->clear(this->m_background);

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

const sf::Color& VWindow::get_BGColor() const {
    return this->m_background;
}


void VWindow::set_BGColor(const sf::Color& _bgcolor) {
    this->m_background = _bgcolor;
}

















///
/// Engine
///



Engine::Engine(const string WINDOW_TITLE) : m_isRunning(false)
{    
    VDebuger::print("ENGINE :: INIT");

    //window
    window = make_unique<VWindow>();
    if (!window->init(WINDOW_TITLE))
    {
        VDebuger::print("<ERROR> ENGINE :: WINDOW INIT ERROR");
    }
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

        //update silnika
        this->taskHandling();
        this->onUpdate(deltaTime);

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

}





///
/// getters
///

VWindow* Engine::get_window() const
{
    return this->window.get();
}

