#ifndef ENGINE_H
#define ENGINE_H

//sfml - graphics library
#include <SFML/Graphics.hpp>

//system
#include <string>
#include <memory>

//engine
#include "engine/core/Scene.h"
#include "engine/core/Vector2.h"

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
    Scene* get_currentScene() const;


    //Menadzer scen.
    //Fragment klasy zarzadzajacy scenami.

private:
    struct SceneLoadData
    {
    private:
        string name = string();
        bool keepChanges = bool(false);

    public:
        void set(string name, bool keepChanges);
        void dispose();
        bool isInited();
        const string& getName() const;
        const bool& getKeepChanges() const;
    };

private:
    map<string, unique_ptr<Scene>> scenes;
    Scene* currentScene;
    SceneLoadData sceneLoadData;

protected:

    ///
    /// \brief Metoda budujaca obiekt sceny w pamieci. Zwraca surowy wskaznik na utworzona scene.
    /// \details Po zakonczeniu programu pamiec jest zwalniana automatycznie. WSKAZNIKA NIE NALEZY CZYSZCIC RECZNIE SLOWEM DELETE.
    /// Aby stworzyc nowa scene:
    /// 1. Utworz klase dziedziczaca publicznie po klasie Scene - przykladowo class MainScene.
    /// 2. W kontruktorze klasy bedacej rodzajem klasy Engine wywolaj metode createScene<T>(string) - przykladowo createScene<MainScene>("SceneGlowna")
    /// \tparam T* Klasa bedaca rodzajem klasy Scene.
    /// \param name Nazwa sceny musi byc unikalna, proba utworzenia sceny o istniejacej nazwie zwroci blad.
    /// \param chunkSize Dlugosc krawedzi kwadratowych komorek tworzacych siatke. Optymalizuje obslugiwanie interakcji miedzy obiektami.
    /// \return
    ///

    template <typename SCENE_TYPE>
    typename enable_if<is_base_of<Scene, SCENE_TYPE>::value, Scene*>::type
    createScene(const string& name, unsigned int chunkSize = 500)
    {
        //check
        if (this->scenes.find(name) != this->scenes.end())
        {
            VDebuger::print("<ERROR> ENGINE :: CREATE_SCENE :: scene with name '", name, "' already exist");

            throw runtime_error("ENGINE :: CREATE_SCENE :: scene create error");
            return nullptr;
        }

        //create
        this->scenes[name] = make_unique<SCENE_TYPE>();
        this->scenes[name]->init(this, name, chunkSize);

        //log
        VDebuger::print("ENGINE :: CREATE_SCENE :: scene", name, "created");

        //return
        return this->scenes[name].get();
    }

public:

    ///
    /// \brief Metoda zmienia scene na podana w argumencie.
    /// \details Argument bool okresla czy poprzednio uzywana scena ma zostac wyczyszczona czy zachowana w pamieci wraz ze wszystkimi zmianami.
    /// \param name Nazwa wczytywanej sceny.
    /// \param keepChanges True - zachowanie zmian, False - zwolnienie pamieci.
    ///

    void changeScene(const string name, bool keepChanges = false);


private:
    void loadScene(); //Ta metoda jest wywolywana przez silnik.
};

#endif // ENGINE_H
