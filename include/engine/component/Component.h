#ifndef COMPONENT_H
#define COMPONENT_H

class Engine;
class Object;

typedef unsigned int uint;

///
/// \brief Struktura przechowujaca priorytety wykonywania wszystkich Componentow, ktore go posiadaja.
/// \details Componenty z najnizsza wartoscia sa wykonywane pierwsze.
///

struct COMPONENT_PRIORITY
{
};

///
/// \brief Klasa bazowa dla wszystkich Componentow. Kazdy Component musi byc rodzajem tej klasy.
///

class Component
{
    friend class Object;

private:
    Engine* game;
    Object* object;
    uint type_hash_code;

public:
    const float	PRIORITY;

    Component(float PRIORITY = 0.0f);
    virtual ~Component();

    //getters
    const uint get_typeHashCode() const;
    Engine* getGame() const;
    Object* getObject() const;

protected:
    virtual bool init(Engine* game, Object* parent); //Ta metoda jest wywolywana przez silnik.


    /*
    * Metody sa przeznaczone do przechowywania wlasnej niestandardowej logiki.
    * Sa domyslnie puste.
    * Te metody sa wywolywane przez silnik.
    */

    virtual void onAwake(); //kiedy Component jest tworzony.
    virtual void onStart(); //w pierwszej klatce po zaladowaniu sceny.
    virtual void onUpdate(float deltaTime); //w kazdej klatce.
    virtual void onLateUpdate(float deltaTime); //w kazdej klatce, po wykonaniu onUpdate(float) dla kazdego obiektu.

private:
    void onCreate(uint type_hash_code); //Ta metoda jest wywolywana przez silnik.

};

#endif // COMPONENT_H
