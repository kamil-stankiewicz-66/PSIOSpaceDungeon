#include "game/core/ScriptableObject.h"
#include "engine/core/Debuger.h"
#include "game/core/Asset.h"
#include "game/core/Parameter.h"



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

const map<uint, unique_ptr<WeaponData>>& WeaponSO::getAll() {
    return WeaponSO::weapons;
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

        fists->id = 0u;
        fists->name = "Fists";

        fists->type = WeaponData::Type::Melee;
        fists->coins = 0u;
        fists->attackTimeOut = 1500.0f;
        fists->damage = 50.0f;
        fists->range = 80.0f;

        WeaponSO::add(fists);
    }

    //basic rifle
    {
        WeaponData* rifle = new WeaponData;

        rifle->id = 1u;
        rifle->name = "Assault Rifle";
        rifle->textureRef = Asset::Graphics::ASSAULT_RIFLE_01.data();

        rifle->type = WeaponData::Type::Gun;
        rifle->coins = 10u;
        rifle->attackTimeOut = 500.0f;
        rifle->damage = 10.0f;
        rifle->range = 400.0f;

        WeaponSO::add(rifle);
    }

    //shotgun
    {
        WeaponData* shotgun = new WeaponData;

        shotgun->id = 2u;
        shotgun->name = "Shotgun";
        shotgun->textureRef = Asset::Graphics::SHOTGUN_01.data();
        shotgun->type = WeaponData::Type::Gun;
        shotgun->coins = 25u;
        shotgun->attackTimeOut = 800.0f;
        shotgun->damage = 20.0f;
        shotgun->range = 200.0f;

        WeaponSO::add(shotgun);
    }


    //machine pistol
    {
        WeaponData* machine = new WeaponData;

        machine->id = 3u;
        machine->name = "Machine Pistol";
        machine->textureRef = Asset::Graphics::MASHINE_PISTOL_01.data();
        machine->type = WeaponData::Type::Gun;
        machine->coins = 20u;
        machine->attackTimeOut = 150.0f;
        machine->damage = 5.0f;
        machine->range = 200.0f;

        WeaponSO::add(machine);
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

void EntitySO::getStats(const EntityData::Attribute& attribute, float& health, float& strength)
{
    switch (attribute) {
    case EntityData::Attribute::HeavyTank:
        health = Parameters::get_entity_heavyTank_health();
        strength = Parameters::get_entity_heavyTank_strength();
        break;

    case EntityData::Attribute::Tank:
        health = Parameters::get_entity_tank_health();
        strength = Parameters::get_entity_tank_strength();
        break;

    case EntityData::Attribute::Medium:
        health = Parameters::get_entity_medium_health();
        strength = Parameters::get_entity_medium_strength();
        break;

    case EntityData::Attribute::Assasin:
        health = Parameters::get_entity_assasin_health();
        strength = Parameters::get_entity_assasin_strength();
        break;

    case EntityData::Attribute::LightAssasin:
        health = Parameters::get_entity_lightAssasin_health();
        strength = Parameters::get_entity_lightAssasin_strength();
        break;

    default:
        health = 0.0f;
        strength = 0.0f;
        break;
    }
}

const map<uint, unique_ptr<EntityData>>& EntitySO::getAll() {
    return EntitySO::entities;
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
    //zombie
    {
        EntityData* zombie = new EntityData;

        zombie->id = entities.size();
        zombie->name = "Zombie";
        zombie->textureRef = Asset::Graphics::ZOMBIE_BASIC.data();

        zombie->type = EntityData::Type::Basic;
        zombie->attribute = EntityData::Attribute::Medium;
        zombie->level = 3u;
        zombie->weaponID = 0u;
        zombie->walkSpeed = 2.0f;
        zombie->runSpeed = 3.0f;
        zombie->scale = 2.0f;

        EntitySO::add(zombie);
    }

    //zombie green
    {
        EntityData* zombieGreen = new EntityData;

        zombieGreen->id = entities.size();
        zombieGreen->name = "Green Zombie";
        zombieGreen->textureRef = Asset::Graphics::ZOMBIE_GREEN.data();

        zombieGreen->type = EntityData::Type::Basic;
        zombieGreen->attribute = EntityData::Attribute::Tank;
        zombieGreen->level = 4u;
        zombieGreen->weaponID = 0u;
        zombieGreen->walkSpeed = 1.0f;
        zombieGreen->runSpeed = 3.0f;
        zombieGreen->scale = 2.0f;

        EntitySO::add(zombieGreen);
    }

    //zombie short
    {
        EntityData* zombieShort = new EntityData;

        zombieShort->id = entities.size();
        zombieShort->name = "Short Zombie";
        zombieShort->textureRef = Asset::Graphics::ZOMBIE_SHORT.data();

        zombieShort->type = EntityData::Type::Basic;
        zombieShort->attribute = EntityData::Attribute::Assasin;
        zombieShort->level = 2u;
        zombieShort->weaponID = 0u;
        zombieShort->walkSpeed = 5.0f;
        zombieShort->runSpeed = 6.0f;
        zombieShort->scale = 2.0f;

        EntitySO::add(zombieShort);
    }

    //zombie small
    {
        EntityData* zombieSmall = new EntityData;

        zombieSmall->id = entities.size();
        zombieSmall->name = "Small Zombie";
        zombieSmall->textureRef = Asset::Graphics::ZOMBIE_SMALL.data();

        zombieSmall->type = EntityData::Type::Basic;
        zombieSmall->attribute = EntityData::Attribute::Assasin;
        zombieSmall->level = 1u;
        zombieSmall->weaponID = 0u;
        zombieSmall->walkSpeed = 2.0f;
        zombieSmall->runSpeed = 5.5f;
        zombieSmall->scale = 2.0f;

        EntitySO::add(zombieSmall);
    }

    //zombie tall
    {
        EntityData* zombieTall = new EntityData;

        zombieTall->id = entities.size();
        zombieTall->name = "Tall Zombie";
        zombieTall->textureRef = Asset::Graphics::ZOMBIE_TALL.data();

        zombieTall->type = EntityData::Type::Basic;
        zombieTall->attribute = EntityData::Attribute::HeavyTank;
        zombieTall->level = 5u;
        zombieTall->weaponID = 0u;
        zombieTall->walkSpeed = 0.5f;
        zombieTall->runSpeed = 1.0f;
        zombieTall->scale = 2.0f;

        EntitySO::add(zombieTall);
    }

    //zombie skeleton
    {
        EntityData* skeleton = new EntityData;

        skeleton->id = entities.size();
        skeleton->name = "Skeleton";
        skeleton->textureRef = Asset::Graphics::ZOMBIE_SKELETON.data();

        skeleton->type = EntityData::Type::Basic;
        skeleton->attribute = EntityData::Attribute::LightAssasin;
        skeleton->level = 5u;
        skeleton->weaponID = 0u;
        skeleton->walkSpeed = 0.5f;
        skeleton->runSpeed = 6.5f;
        skeleton->scale = 2.0f;

        EntitySO::add(skeleton);
    }

    //orc
    {
        EntityData* orc = new EntityData;

        orc->id = entities.size();
        orc->name = "Orc";
        orc->textureRef = Asset::Graphics::ORC_BASIC.data();

        orc->type = EntityData::Type::Basic;
        orc->attribute = EntityData::Attribute::Assasin;
        orc->level = 2u;
        orc->weaponID = 1u;
        orc->walkSpeed = 2.5f;
        orc->runSpeed = 5.0f;
        orc->scale = 2.2f;

        EntitySO::add(orc);
    }

    //armored orc
    {
        EntityData* orcArmored = new EntityData;

        orcArmored->id = entities.size();
        orcArmored->name = "Armored Orc";
        orcArmored->textureRef = Asset::Graphics::ORC_ARMORED.data();

        orcArmored->type = EntityData::Type::Basic;        
        orcArmored->attribute = EntityData::Attribute::Tank;
        orcArmored->level = 3u;
        orcArmored->weaponID = 2u;
        orcArmored->walkSpeed = 2.0f;
        orcArmored->runSpeed = 4.0f;
        orcArmored->scale = 2.4f;

        EntitySO::add(orcArmored);
    }

    //masked orc
    {
        EntityData* orcMasked = new EntityData;

        orcMasked->id = entities.size();
        orcMasked->name = "Masked Orc";
        orcMasked->textureRef = Asset::Graphics::ORC_MASKED.data();

        orcMasked->type = EntityData::Type::Basic;
        orcMasked->attribute = EntityData::Attribute::Assasin;
        orcMasked->level = 3u;
        orcMasked->weaponID = 1u;
        orcMasked->walkSpeed = 2.5f;
        orcMasked->runSpeed = 5.0f;
        orcMasked->scale = 2.2f;

        EntitySO::add(orcMasked);
    }

    //orc shaman
    {
        EntityData* orcShaman = new EntityData;

        orcShaman->id = entities.size();
        orcShaman->name = "Orc Shaman";
        orcShaman->textureRef = Asset::Graphics::ORC_SHAMAN.data();

        orcShaman->type = EntityData::Type::Basic;
        orcShaman->attribute = EntityData::Attribute::Medium;
        orcShaman->level = 1u;
        orcShaman->weaponID = 2u;
        orcShaman->walkSpeed = 2.0f;
        orcShaman->runSpeed = 4.5f;
        orcShaman->scale = 2.0f;

        EntitySO::add(orcShaman);
    }

    //orc veteran
    {
        EntityData* orcVeteran = new EntityData;

        orcVeteran->id = entities.size();
        orcVeteran->name = "Orc Veteran";
        orcVeteran->textureRef = Asset::Graphics::ORC_VETERAN.data();

        orcVeteran->type = EntityData::Type::Basic;
        orcVeteran->attribute = EntityData::Attribute::Assasin;
        orcVeteran->level = 3u;
        orcVeteran->weaponID = 3u;
        orcVeteran->walkSpeed = 2.8f;
        orcVeteran->runSpeed = 5.5f;
        orcVeteran->scale = 2.3f;

        EntitySO::add(orcVeteran);
    }
}

