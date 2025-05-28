#ifndef SCENE_H
#define SCENE_H

#include "engine/object/Object.h"

#include <functional>
#include <map>
#include <memory>
#include <unordered_set>
#include <list>

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
    unsigned int next_id_for_go;

    OBJ_MAP_TYPE objects;
    unordered_set<shared_ptr<Object>> WIDeadBodyCleanupCell;
    list<shared_ptr<Object>> buffor_objectsToCreate;
    unordered_set<Object*> buffor_objectsToKill;

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


public:

    ///
    /// \brief A method that removes an object from the scene.
    /// \param Object* A pointer to the object we want to remove from the scene.
    /// \param critical A flag that determines whether the object should be completely removed from memory [critical = true]
    /// or safely moved to the WIDeadBodyCleanupCell collection [critical = false] (recommended).
    ///

    void killObject(Object*, bool critical = false);



    // Template methods.

public:

    ///
    /// \brief Metoda jest przeznaczona do tworzenia obiektow i dodawania ich do sceny.
    /// Metoda zwraca surowy wskaźnik do utworzonego obiektu.
    /// Po zakonczeniu programu pamiec jest zwalniana automatycznie. WSKAZNIKA NIE NALEZY CZYSZCIC RECZNIE SLOWEM DELETE.
    /// Aby uworzyc obiekt:
    /// 1. Utworz klase dziedziczaca publicznie po klasie GameObject lub UIObject - przykladowo class Entity.
    /// 2. W dowolnym miejscu wywolaj metode createObject<Entity>(), aby obiekt pojawil sie na scenie.
    /// Aby utworzyc obiekt pojawiajacy sie na scenie domyslnie skorzystaj z metody loadObjects();
    /// \tparam T Typ musi być rodzajem klasy Object.
    /// \param _renderLayer Warstwa, na której obiekt będzie renderowany.
    /// \param _parent Obiekt nadrzędny obiektu, który jest tworzony.
    /// \return T*
    ///

    template <typename T>
    typename enable_if<is_base_of<Object, T>::value, T*>::type
    createObject(unsigned int _renderLayer = 0, Object* _parent = nullptr)
    {
        shared_ptr<Object> go_ptr = make_shared<T>();

        //init
        go_ptr->setParent(_parent);
        bool m_init = go_ptr->init(
            this->game,
            typeid(T).hash_code(),
            next_id_for_go++
            );

        if (!m_init)
        {
            VDebuger::print("<ERROR> :: SCENE :: CREATE_OBJECT :: go init error");

            return nullptr;
        }

        //add
        if (m_isThisFirstFrame)
        {
            objects[_renderLayer][go_ptr->hashId][go_ptr->id] = go_ptr;
            go_ptr->setEnable(true);

            //log
            VDebuger::print("SCENE_MANAGER :: obj:", go_ptr.get(), "id =", go_ptr->id, "hash_id =", go_ptr->hashId, "added to scene:", this->name);
        }
        else
        {
            buffor_objectsToCreate.push_back(go_ptr);

            //log
            VDebuger::print("SCENE_MANAGER :: obj:", go_ptr.get(), "id =", go_ptr->id, "hash_id =", go_ptr->hashId, "added to buffor in scene:", this->name);
        }

        //call awake()
        go_ptr->onAwake();

        return dynamic_cast<T*>(go_ptr.get());
    }

};

#endif // SCENE_H
