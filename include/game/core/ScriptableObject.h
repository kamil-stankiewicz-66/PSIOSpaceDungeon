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

#endif // SCRIPTABLEOBJECT_H
