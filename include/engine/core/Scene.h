#ifndef SCENE_H
#define SCENE_H

#include <string>

using namespace std;

class Engine;



///
/// \brief Klasa bazowa dla wszystkich scen. Kazda scene musi byc rodzajem tej klasy.
/// \details Pamietaj o implementacji metody abstrakcyjnej !!!
///

class Scene
{
    friend class Engine;

private:
    Engine* game;
    string name;

    bool m_isThisFirstFrame;

public:
    Scene();
    ~Scene();
    void init(Engine* game, const string& name, unsigned int chunkSize);

private:
    void load();
    void dispose();


public:

    ///Metoda resetujaca scene.
    void reload();

    ///Zwraca true jesli jest to pierwsza klatka od wczytania tej sceny.
    const bool isThisFirstFrame() const;


    //setters
    void set_globalScale(const float&);

    //getters
    const Engine* getGame() const;
    const string& get_name() const;
    const float& get_globalScale() const;

private:
    void update(float deltaTime); //Ta metoda jest wywolywana przez silnik.

};

#endif // SCENE_H
