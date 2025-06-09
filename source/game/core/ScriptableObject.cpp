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

        fists->id = 0u;
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

        zombie->id = 0u;
        zombie->name = "Zombie";
        zombie->textureRef = Asset::Graphics::ZOMBIE_BASIC.data();

        zombie->type = EntityData::Type::Basic;
        zombie->weaponID = 0u;
        zombie->walkSpeed = 2.0f;
        zombie->runSpeed = 3.0f;
        zombie->scale = 2.0f;

        zombie->healthID = 0u; // Basic Health
        EntitySO::add(zombie);
    }

    //zombie green
    {
        EntityData* zombieGreen = new EntityData;

        zombieGreen->id = 1u;
        zombieGreen->name = "Green Zombie";
        zombieGreen->textureRef = Asset::Graphics::ZOMBIE_GREEN.data();

        zombieGreen->type = EntityData::Type::Basic;
        zombieGreen->weaponID = 0u;
        zombieGreen->walkSpeed = 1.0f;
        zombieGreen->runSpeed = 3.0f;
        zombieGreen->scale = 2.0f;
        zombieGreen->healthID = 0u; // Basic Health

        EntitySO::add(zombieGreen);
    }

    //zombie short
    {
        EntityData* zombieShort = new EntityData;

        zombieShort->id = 2u;
        zombieShort->name = "Short Zombie";
        zombieShort->textureRef = Asset::Graphics::ZOMBIE_SHORT.data();

        zombieShort->type = EntityData::Type::Basic;
        zombieShort->weaponID = 0u;
        zombieShort->walkSpeed = 5.0f;
        zombieShort->runSpeed = 6.0f;
        zombieShort->scale = 2.0f;
        zombieShort->healthID = 0u; // Basic Health

        EntitySO::add(zombieShort);
    }

    //zombie small
    {
        EntityData* zombieSmall = new EntityData;

        zombieSmall->id = 3u;
        zombieSmall->name = "Small Zombie";
        zombieSmall->textureRef = Asset::Graphics::ZOMBIE_SMALL.data();

        zombieSmall->type = EntityData::Type::Basic;
        zombieSmall->weaponID = 0u;
        zombieSmall->walkSpeed = 2.0f;
        zombieSmall->runSpeed = 5.5f;
        zombieSmall->scale = 2.0f;

        zombieSmall->healthID = 0u; // Basic Health
        EntitySO::add(zombieSmall);
    }

    //zombie tall
    {
        EntityData* zombieTall = new EntityData;

        zombieTall->id = 4u;
        zombieTall->name = "Tall Zombie";
        zombieTall->textureRef = Asset::Graphics::ZOMBIE_TALL.data();

        zombieTall->type = EntityData::Type::Basic;
        zombieTall->weaponID = 0u;
        zombieTall->walkSpeed = 0.5f;
        zombieTall->runSpeed = 1.0f;
        zombieTall->scale = 2.0f;
        zombieTall->healthID = 0u; // Basic Health


        EntitySO::add(zombieTall);
    }

    //zombie skeleton
    {
        EntityData* skeleton = new EntityData;

        skeleton->id = 5u;
        skeleton->name = "Skeleton";
        skeleton->textureRef = Asset::Graphics::ZOMBIE_SKELETON.data();

        skeleton->type = EntityData::Type::Basic;
        skeleton->weaponID = 0u;
        skeleton->walkSpeed = 0.5f;
        skeleton->runSpeed = 6.5f;
        skeleton->scale = 2.0f;
        skeleton->healthID = 0u; // Basic Health

        EntitySO::add(skeleton);
    }
    //armored orc
    {
        EntityData* orcArmored = new EntityData;

        orcArmored->id = 7u;
        orcArmored->name = "Armored Orc";
        orcArmored->textureRef = Asset::Graphics::ORC_ARMORED.data();

        orcArmored->type = EntityData::Type::Basic;
        orcArmored->weaponID = 1u;
        orcArmored->walkSpeed = 2.0f;
        orcArmored->runSpeed = 4.0f;
        orcArmored->scale = 2.4f;
        orcArmored->healthID = 1u; // Elite Health

        EntitySO::add(orcArmored);
    }

    //masked orc
    {
        EntityData* orcMasked = new EntityData;

        orcMasked->id = 8u;
        orcMasked->name = "Masked Orc";
        orcMasked->textureRef = Asset::Graphics::ORC_MASKED.data();

        orcMasked->type = EntityData::Type::Basic;
        orcMasked->weaponID = 1u;
        orcMasked->walkSpeed = 2.5f;
        orcMasked->runSpeed = 5.0f;
        orcMasked->scale = 2.2f;
        orcMasked->healthID = 1u; // Elite Health

        EntitySO::add(orcMasked);
    }
//orc shaman
{
    EntityData* orcShaman = new EntityData;

    orcShaman->id = 9u;
    orcShaman->name = "Orc Shaman";
    orcShaman->textureRef = Asset::Graphics::ORC_SHAMAN.data();

    orcShaman->type = EntityData::Type::Basic;
    orcShaman->weaponID = 1u;
    orcShaman->walkSpeed = 2.0f;
    orcShaman->runSpeed = 4.5f;
    orcShaman->scale = 2.0f;
    orcShaman->healthID = 1u; // Elite Health

    EntitySO::add(orcShaman);
}

//orc veteran
{
    EntityData* orcVeteran = new EntityData;

    orcVeteran->id = 10u;
    orcVeteran->name = "Orc Veteran";
    orcVeteran->textureRef = Asset::Graphics::ORC_VETERAN.data();

    orcVeteran->type = EntityData::Type::Basic;
    orcVeteran->weaponID = 1u;
    orcVeteran->walkSpeed = 2.8f;
    orcVeteran->runSpeed = 5.5f;
    orcVeteran->scale = 2.3f;
    orcVeteran->healthID = 1u; // Elite Health

    EntitySO::add(orcVeteran);
}
}

///
/// Health
///


// mapa ze wszystkimi danymi zdrowia
map<uint, unique_ptr<HealthData>> HealthSO::healthDataMap;


// funkcja ktora pobiera dane zdrowia
const HealthData* HealthSO::get(const uint& id)

{
    auto it = healthDataMap.find(id);
    if (it != healthDataMap.end() && it->second)
    {
        return it->second.get();
    }
    else
    {

        VDebuger::print("<ERROR> HEALTH_SO :: health data with id", id, "not exist");
        return nullptr;
    }
}


const map<uint, unique_ptr<HealthData>>& HealthSO::getAll()
{
    return HealthSO::healthDataMap;
}

//Dodaje nowy obiekt HealthData do mapy
void HealthSO::add(HealthData* so)
{
    auto it = healthDataMap.find(so->id);
    if (it == healthDataMap.end() && so)
    {
        healthDataMap[so->id] = unique_ptr<HealthData>(so);
    }
}


void HealthSO::init()
{
    {
        // Zwykle zdrowie
        HealthData* basicHealth = new HealthData;
        basicHealth->id = 0u;
        basicHealth->name = "Basic Health";
        basicHealth->textureRef = "";
        basicHealth->maxHealth = 100.0f;
        basicHealth->regenRate = 2.0f;
        HealthSO::add(basicHealth);
    }

    {
        // elite
        HealthData* eliteHealth = new HealthData;
        eliteHealth->id = 1u;
        eliteHealth->name = "Elite Health";
        eliteHealth->textureRef = "";
        eliteHealth->maxHealth = 250.0f;
        eliteHealth->regenRate = 5.0f;
        HealthSO::add(eliteHealth);
    }
}
