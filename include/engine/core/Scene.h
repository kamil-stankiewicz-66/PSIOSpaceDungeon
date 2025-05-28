#ifndef SCENE_H
#define SCENE_H

#include "engine/object/Object.h"

#include <string>
#include <map>
#include <memory>

using namespace std;

class Engine;

//Alias for the main objects map type [renderLayer, hashID, id, obj_ptr]
using OBJ_MAP_TYPE = map<unsigned int, map<size_t, map<unsigned int, shared_ptr<Object>>>>;



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
    float globalScale; //the scaling factor of all objects during creation

    OBJ_MAP_TYPE objects;

public:
    Scene();
    ~Scene();
    void init(Engine* game, const string& name, unsigned int chunkSize);

private:
    void load();
    void dispose();

protected:

    ///
    /// \brief Metoda przeznaczona do tworzenia obiektow umieszczanych domyslnie na scenie oraz ustawiania ich domyslnych parametrow.
    /// \details Wiecej informacji o tworzeniu obiekow w opisie metody createObject<T>();
    ///

    virtual void loadObjects() = 0;


public:

    ///Metoda resetujaca scene.
    void reload();

    ///Zwraca true jesli na scenie nie ma obiektow.
    const bool isEmpty() const;

    ///Zwraca true jesli jest to pierwsza klatka od wczytania tej sceny.
    const bool isThisFirstFrame() const;


    //setters
    void set_globalScale(const float&);

    //getters
    const Engine* getGame() const;
    const string& get_name() const;
    const float& get_globalScale() const;
    const OBJ_MAP_TYPE& get_objects() const;

private:
    void update(float deltaTime); //Ta metoda jest wywolywana przez silnik.

};

#endif // SCENE_H
