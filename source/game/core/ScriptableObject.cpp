#include "game/core/ScriptableObject.h"
#include "game/core/Asset.h"


//static var
map<uint, unique_ptr<WeaponData>> WeaponSO::weapons;


///
/// getter
///

const WeaponData* WeaponSO::get(const uint& id)
{
    auto it = weapons.find(id);

    if (it != weapons.end() && it->second)
    {
        return it->second.get();
    }
    else
    {
        VDebuger::print("<ERROR> WeaponData :: weapon with id", id, "not exist");
        return nullptr;
    }
}


///
/// add
///

void WeaponSO::add(WeaponData* so)
{
    if (!get(so->id)) {
        weapons[so->id] = unique_ptr<WeaponData>(so);
    }
}


///
/// init
///

void WeaponSO::init()
{
    //fists
    {
        WeaponData* fists = new WeaponData;

        fists->id = 0;
        fists->name = "Fists";
        fists->coins = 10;

        fists->attackTimeOut = 1500.0f;
        fists->damage = 1.0f;
        fists->range = 5.0f;

        WeaponSO::add(fists);
    }

    //basic rifle
    {
        WeaponData* rifle = new WeaponData;

        rifle->id = 1;
        rifle->name = "Assault Rifle";
        rifle->textureRef = Asset::Graphics::ASSAULT_RIFLE_01.data();
        rifle->coins = 10;

        rifle->attackTimeOut = 1000.0f;
        rifle->damage = 10.0f;
        rifle->range = 400.0f;

        WeaponSO::add(rifle);
    }
}
