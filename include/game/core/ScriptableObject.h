#ifndef SCRIPTABLEOBJECT_H
#define SCRIPTABLEOBJECT_H

#include <map>
#include <memory>
#include <string>
using namespace std;
using uint = unsigned int;



///
/// Base data object.
///

struct ScriptableObject
{
    uint id;
    string name;
    string textureRef;
};



///
/// \brief WeaponData scriptable objects.
///

struct WeaponData : ScriptableObject
{
    enum class Type { Melee, Gun };

    Type type;
    uint coins;
    float range;
    float damage;
    float attackTimeOut;
};

class WeaponSO
{
    friend class Game;

    //all weapon scriptable objects
    static map<uint, unique_ptr<WeaponData>> weapons;

public:
    static const WeaponData* get(const uint& id);

private:
    static void add(WeaponData*);
    static void init();
};


///
/// \brief EntitiData scriptable objects.
///

struct EntityData : ScriptableObject
{
    enum class Type { Basic };

    Type type;
    uint weaponID;
    uint healthID;
    float walkSpeed;
    float runSpeed;
    float scale;
};

class EntitySO
{
    friend class Game;

    //all entity scriptable objects
    static map<uint, unique_ptr<EntityData>> entities;

public:
    static const EntityData* get(const uint& id);
    static const map<uint, unique_ptr<EntityData>>& getAll();

private:
    static void add(EntityData*);
    static void init();
};

///
/// \brief HealthData scriptable objects.
///

struct HealthData : ScriptableObject

{
    float maxHealth;   // maksymalne hp jakie mozna miec
    float regenRate;   //ile hp na sekunde odzyskuje
};

class HealthSO

{
    friend class Game;

    // mapa z wszystkimi obiektami zdrowia
    static map<uint, unique_ptr<HealthData>> healthDataMap;


public:
    //  pobiera dane zdrowia po ida
    static const HealthData* get(const uint& id);

    // zwraca cala mape danych zdrowia
    static const map<uint, unique_ptr<HealthData>>& getAll();

private:

    //dodaje nowy wpis do mapy
    static void add(HealthData*);

    static void init();
};


#endif // SCRIPTABLEOBJECT_H
