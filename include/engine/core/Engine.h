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


static constexpr string_view WINDOW_TITLE_DEFAULT = "VEngine2 v.3.1";



///
/// \brief Structure handling the SFML window and basic information about the window.
///

class VWindow
{
    friend class Engine;

    ///
    /// \brief Structure storing the positions of the window corners.
    /// \details Designed for positioning interface elements.
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

    string m_windowTitle;
    bool m_isFullscreen;

    bool init(const string WINDOW_TITLE, const bool fullscreen);
    bool makeWindow();

public:
    VWindow();
    ~VWindow();

    //change window style
    void setFullscreen(const bool);

    //Clears the window and displays the color m_background
    void clear();

    //Is the window ready to use?
    bool isInited() const;

    //getters
    sf::RenderWindow* get_renderwindow() const;
    const sf::VideoMode& get_displaymode() const;
    const CornerPositions& get_cornerPositions() const;
    const sf::Color& get_BGColor() const;

    void setBGColor(const sf::Color&);
};



///
/// \brief Main engine class.
/// \details To create a new game, make a <Game> class that inherits from this class.
/// In main, create an object of this class.
/// To start the engine loop, call the run() method on the <Game> class object.
/// To stop the engine loop, call shutdown() on the <Game> class object.
///

class Engine
{
private:
    unique_ptr<VWindow> window;
    bool m_isRunning;

protected:

    //Global logic – runs every cycle, regardless of the active scene.
    //The method is empty by default.
    virtual void onUpdate(float deltaTime);

public:
    Engine(const string WINDOW_TITLE = WINDOW_TITLE_DEFAULT.data(), const bool fullscreen = true);
    virtual ~Engine();


    ///
    /// \brief Main engine loop.
    /// \param MAX_FPS Frame rate limit – default is 60.
    /// \return
    ///

    int run(const unsigned int MAX_FPS = 60);


    ///
    /// \brief Method that stops the main engine loop and closes the application.
    ///

    void shutdown();


private:
    void taskHandling();


public:
    VWindow* get_window() const;
    Scene* get_currentScene() const;
    Scene* get_scene(const string& name) const;


    //Scene manager.
    //Part of the class for managing scenes.

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
    /// \brief Method that creates a scene object in memory. Returns a raw pointer to the created scene.
    /// \details After the program ends, memory is freed automatically. DO NOT manually delete the POINTER using delete.
    /// To create a new scene:
    /// 1. Create a class that publicly inherits from the Scene class – for example, class MainScene.
    /// 2. In the constructor of the class that is a type of Engine, call the method createScene<T>(string) – for example, createScene<MainScene>("MainScene").
    /// \tparam T* Class that is a type of Scene.
    /// \param name The scene name must be unique; trying to create a scene with an existing name will cause an error.
    /// \param chunkSize The length of the square cells that form the grid. Optimizes handling interactions between objects.
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
    /// \brief Method changes the scene to the one given in the argument.
    /// \details The bool argument specifies whether the previously used scene should be cleared or kept in memory with all changes.
    /// \param name Name of the scene to load.
    /// \param keepChanges True – keep changes, False – free memory.
    ///

    void changeScene(const string name, bool keepChanges = false);


private:
    void loadScene(); //This method is called by the engine.
};

#endif // ENGINE_H
