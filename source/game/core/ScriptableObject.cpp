#include "game/core/ScriptableObject.h"
#include "engine/core/Debuger.h"
#include "game/core/Asset.h"



///
/// Weapons
///


//static var
map<uint, unique_ptr<WeaponData>> WeaponSO::weapons;


//getter

const WeaponData* WeaponSO::get(const uint& id)
{
    auto it = weapons.find(id);

    if (it != weapons.end() && it->second)
    {
        return it->second.get();
    }
    else
    {
        VDebuger::print("<ERROR> WEAPON_SO :: weapon with id", id, "not exist");
        return nullptr;
    }
}


//add

void WeaponSO::add(WeaponData* so)
{
    auto it = weapons.find(so->id);

    if (it == weapons.end() && so)
    {
        weapons[so->id] = unique_ptr<WeaponData>(so);
    }
}


//init

void WeaponSO::init()
{
    //fists
    {
        WeaponData* fists = new WeaponData;

        fists->id = 0;
        fists->name = "Fists";

        fists->type = WeaponData::Type::Melee;
        fists->coins = 0u;
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

        rifle->type = WeaponData::Type::Gun;
        rifle->coins = 10u;
        rifle->attackTimeOut = 500.0f;
        rifle->damage = 10.0f;
        rifle->range = 400.0f;

        WeaponSO::add(rifle);
    }
}



///
/// Entities
///


//static var
map<uint, unique_ptr<EntityData>> EntitySO::entities;


//getter

const EntityData* EntitySO::get(const uint& id)
{
    auto it = entities.find(id);

    if (it != entities.end() && it->second)
    {
        return it->second.get();
    }
    else
    {
        VDebuger::print("<ERROR> ENTITY_SO :: weapon with id", id, "not exist");
        return nullptr;
    }
}


//add

void EntitySO::add(EntityData* so)
{
    auto it = entities.find(so->id);

    if (it == entities.end() && so)
    {
        entities[so->id] = unique_ptr<EntityData>(so);
    }
}


//init

void EntitySO::init()
{
    // //fists
    // {
    //     WeaponData* fists = new WeaponData;

    //     fists->id = 0;
    //     fists->name = "Fists";
    //     fists->coins = 10;

    //     fists->attackTimeOut = 1500.0f;
    //     fists->damage = 1.0f;
    //     fists->range = 5.0f;

    //     WeaponSO::add(fists);
    // }

    //zombie
    {
        EntityData* zombie = new EntityData;

        zombie->id = 0u;
        zombie->name = "Zombie";
        zombie->textureRef = Asset::Graphics::ZOMBIE_BASIC.data();

        zombie->weaponID = 0u;
        zombie->walkSpeed = 2.0f;
        zombie->runSpeed = 4.0f;
    }
}





