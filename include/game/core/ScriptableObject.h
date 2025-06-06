#ifndef SCRIPTABLEOBJECT_H
#define SCRIPTABLEOBJECT_H

#include "game/weapon/Weapon.h"

///
/// \brief Scriptable objects.
///

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

#endif // SCRIPTABLEOBJECT_H
