#ifndef ENGINE_H
#define ENGINE_H

//sfml - graphics library
#include <SFML/Graphics.hpp>

//system
#include <string>
#include <memory>

//engine
#include "engine/core/Vector2.h"
#include "engine/core/Debuger.h"

using namespace std;


static constexpr const char* WINDOW_TITLE_DEFAULT = "VEngine2 v.3.1";



///
/// \brief Struktura przechowujaca SDL_Window, SDL_Rednderer i podstawowe informacje o oknie.
///

class VWindow
{
    friend class Engine;

    ///
    /// \brief Struktura przechowujaca pozycje rogow okna.
    /// \details Przeznaczone do pozycjonowania elementow interfejsu.
    ///

    struct CornerPositions
    {
        Vector2 leftUp;
        Vector2 rightUp;
        Vector2 leftDown;
        Vector2 rightDown;

        void init(const sf::VideoMode&);
    };

private:
    unique_ptr<sf::RenderWindow> sfwindow;
    sf::VideoMode displayMode;
    CornerPositions cornerPositions;
    sf::Color m_background;

    bool init(const string WINDOW_TITLE);

public:
    VWindow();
    ~VWindow();

    //czysci okno i wyswietla kolor m_background
    void clear();

    //czy okno jest gotowe do uzycia?
    bool isInited() const;

    //gettery
    sf::RenderWindow* get_renderwindow() const;
    const sf::VideoMode& get_displaymode() const;
    const CornerPositions& get_cornerPositions() const;
    const sf::Color& get_BGColor() const;

    void set_BGColor(const sf::Color&);
};



///
/// \brief Glowna klasa silnika.
/// \details Aby utworzyc nowa gre, stworz klase <Game> dziedziczaca po tej klasie.
/// W main utworz obiekt tej klasy.
/// Aby rozpoczac petle silnika wywolaj metode run() w obiekcie klasy <Game>.
/// Aby przerwac petle silnika wywolaj shutdown() w obiekcie klasy <Game>.
///

class Engine
{
private:
    unique_ptr<VWindow> window;
    bool m_isRunning;

protected:

    //Logika globalna - jest wykonywana w kazdym cyklu, niezaleznie od aktywnej sceny.
    //Metoda jest domyslnie pusta.
    virtual void onUpdate(float deltaTime);

public:
    Engine(const string WINDOW_TITLE = WINDOW_TITLE_DEFAULT);
    virtual ~Engine();


    ///
    /// \brief Glowna petla silnika.
    /// \param MAX_FPS Limit klatek na sekunde - domyslnie 60.
    /// \return
    ///

    int run(const unsigned int MAX_FPS = 60);


    ///
    /// \brief Metoda przerywajaca glowna petle silnika i zamkykajaca aplikacje.
    ///

    void shutdown();


private:
    void taskHandling();


public:
    VWindow* get_window() const;

};

#endif // ENGINE_H
