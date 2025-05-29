#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <set>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "engine/component/Component.h"
#include "engine/core/Debuger.h"
#include "engine/component/Transform.h"

using namespace std;

class Scene;
class Engine;


///
/// \brief Enum reprezentujacy rozne stany obiektu.
///

enum class ObjectState
{
    Normal, Undead, Dead, Reborn, PermaDead
};


///
/// \brief Klasa bazowa obiektu. Kazdy obiekt gry i interfejsu musi byc rodzajem tej klasy.
/// \details Zamiast bezposredniego dziedziczenia po Object, zaleca sie uzycie GameObject przeznanocznych dla obiektow gry i UIObject dla obiektow interfejsu.
///

class Object
{
    friend class Scene;

private:
    bool m_enable;
    ObjectState m_state;
    Engine* game;
    Object* parent;
    vector<Object*> childs;
    map<float, vector<shared_ptr<Component>>> components; //priority, vector
    size_t hashId;
    unsigned int id;
    set<string> tags;

    bool init(Engine* game, const size_t& hashID, const unsigned int& id); //Ta metoda jest wywolywana przez silnik.
    void set_state(ObjectState); //Ta metoda jest wywolywana przez silnik.

protected:
    //Metody przeznaczone do przechowywania logiki obiektow zdefiniowanych przez programiste gry.
    //Te metody sa wywolywana przez silnik...
    virtual void onStart(); //w pierwszej klatce.
    virtual void onAwake(); //kiedy obiekt jest tworzony na scenie.
    virtual void onUpdate(float deltaTime); //w kazdej klatce.


public:
    Object();
    virtual ~Object();

    Engine* getGame() const;

    void setEnable(bool);
    const bool isEnable() const;
    const ObjectState& getState() const;


    //hierarchy

    void setParent(Object*);
    void addChild(Object*);
    void dispose_asChild();
    void dispose_childs();

    const Object* getParent() const;
    const vector<Object*>& getChilds() const;

    bool isChild();
    bool isChildOf(Object*);
    bool try_getParent(Object*& out);


    //identify

    void setTags(const vector<string>&);
    void addTags(const vector<string>&);
    void addTag(const string&);
    void removeTag(const string&);

    const size_t& getHashID() const;
    const unsigned int& getID() const;
    const set<string>& getTags() const;
    const string getTag(const unsigned char& index) const;

    const bool checkTag(const string&) const;


    //components

private:
    void callOnStartInComponents();
    void callOnUpdateInComponents(float deltaTime);
    void callOnLateUpdateInComponents(float deltaTime);

public:

    ///
    /// \brief Metoda jest przeznaczona do tworzenia komponentow i dodawania ich do obiektow.
    /// \details Po zakonczeniu programu pamiec jest zwalniana automatycznie. WSKAZNIKA NIE NALEZY CZYSZCIC RECZNIE SLOWEM DELETE.
    /// Aby uworzyc komponent w dowolnym miejscu wywolaj metode createComponent<TYPE>() na odpowiednim obiekcie.
    /// Silnik zawiera zestaw gotowych komponentow oraz istnieje mozliwosc utworzenia wlasnych.
    /// \return Metoda zwraca surowy wskaznik do utworzonego komponentu.
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, T*>::type
    createComponent()
    {
        bool m_error = false;
        bool m_transformExist = false;

        size_t type_hash_code = typeid(T).hash_code();
        ostringstream _message;

        for (const auto& p_v : components)
        {
            for (const auto& _c : p_v.second)
            {
                if (!m_transformExist && dynamic_cast<Transform*>(_c.get()))
                {
                    m_transformExist = true;
                }

                if (type_hash_code == _c->get_typeHashCode())
                {
                    _message
                        << "<ERROR> :: OBJECT :: CREATE_COMPONENT :: You cannot create second '"
                        << typeid(T).name()
                        << "' component in object: " << this;

                    m_error = true;
                    break;
                }
            }
        }

        if (m_transformExist && is_base_of<Transform, T>::value)
        {
            _message.str("");
            _message
                << "<ERROR> :: OBJECT :: CREATE_COMPONENT :: You cannot create more Transform components in object: " << this;

            m_error = true;
        }

        //report
        if (m_error)
        {
            VDebuger::print("<ERROR>",_message.str());
            throw runtime_error(_message.str());
            return nullptr;
        }


        shared_ptr<Component> _c = make_shared<T>();
        _c->onCreate(type_hash_code);
        _c->init(game, this);
        _c->onAwake();

        this->components[_c->PRIORITY].push_back(_c);

        T* _r = dynamic_cast<T*>(_c.get());
        return _r;
    }

    ///
    /// \brief Metoda wyszukujaca wybranyc komponent w obiekcie.
    /// \details Jesli dany komponent nie zostal utworzony w obiekcie, metoda zwroci nullptr.
    /// \tparam T Klasa bedaca rodzajem klasy Component.
    /// \param polimorhicAllowed Flaga, ktora okresla, czy obiekty bedace rodzajem klasy T sa brane pod uwage.
    /// \return Zwraca wskaznik na wyszukany komponent.
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, T*>::type
    getComponent(bool polimorhicAllowed = false)
    {
        for (const auto& p_v : this->components)
        {
            for (const auto& _comp : p_v.second)
            {
                if (polimorhicAllowed)
                {
                    if (T* _casted = dynamic_cast<T*>(_comp.get())) {
                        return _casted;
                    }
                }
                else if (typeid(T).hash_code() == _comp->get_typeHashCode())
                {
                    if (T* _casted = dynamic_cast<T*>(_comp.get())) {
                        return _casted;
                    }
                }
            }
        }

        return nullptr;
    }

    ///
    /// \brief Metoda wyszukujaca wybrany komponent w obiekcie.
    /// \details Jesli dany komponent zostal znaleziony - nadpisuje refrencje wskaznikiem na wyszukany komponent i zwraca wartosc true.
    /// Jesli dany komponent nie zostal znaleziony, metoda zwroci false.
    /// \tparam Klasa bedaca rodzajem klasy Component.
    /// \param out Referencja na wskaznik na komponent.
    /// \param polimorhicAllowed Flaga, ktora okresla, czy obiekty bedace rodzajem klasy T sa brane pod uwage.
    /// \return True or False
    ///

    template <typename T>
    typename enable_if<is_base_of<Component, T>::value, bool>::type
    try_getComponent(T*& out, bool polimorhicAllowed = true)
    {
        return out = this->getComponent<T>(polimorhicAllowed);
    }


    //basic components

    Transform* transform;

};


///
/// \brief Klasa reprezentujaca pusty obiekt gry.
///

class GameObject : public Object
{
public:
    GameObject();
};


///
/// \brief Klasa reprezentujaca pusty obiekt interfejsu.
///

class UIObject : public Object
{
public:
    UIObject();
};

#endif // OBJECT_H
