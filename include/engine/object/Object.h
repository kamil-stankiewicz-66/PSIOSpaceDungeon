#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

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
    size_t hashId;
    unsigned int id;

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

    const size_t& getHashID() const;
    const unsigned int& getID() const;
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
