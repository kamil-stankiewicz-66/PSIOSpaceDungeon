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

        fists->id = weapons.size();
        fists->name = "Fists";

        fists->type = WeaponData::Type::Melee;
        fists->coins = 0u;
        fists->attackTimeOut = 1500.0f;
        fists->damage = 50.0f;
        fists->range = 80.0f;
        fists->attackSoundRef = Asset::Audio::BITE.data();

        WeaponSO::add(fists);
    }

    //pistol
    {
        WeaponData* pistol = new WeaponData;

        pistol->id = weapons.size();
        pistol->name = "Pistol";
        pistol->textureRef = Asset::Graphics::PISTOL.data();

        pistol->type = WeaponData::Type::Gun;
        pistol->coins = 5u;
        pistol->attackTimeOut = 750.0f;
        pistol->damage = 5.0f;
        pistol->range = 700.0f;
        pistol->attackSoundRef = Asset::Audio::GUN.data();

        WeaponSO::add(pistol);
    }

    //basic rifle
    {
        WeaponData* rifle = new WeaponData;

        rifle->id = weapons.size();
        rifle->name = "Assault Rifle";
        rifle->textureRef = Asset::Graphics::ASSAULT_RIFLE_01.data();

        rifle->type = WeaponData::Type::Gun;
        rifle->coins = 10u;
        rifle->attackTimeOut = 500.0f;
        rifle->damage = 10.0f;
        rifle->range = 800.0f;
        rifle->attackSoundRef = Asset::Audio::GUN.data();

        WeaponSO::add(rifle);
    }

    //shotgun
    {
        WeaponData* shotgun = new WeaponData;

        shotgun->id = weapons.size();
        shotgun->name = "Shotgun";
        shotgun->textureRef = Asset::Graphics::SHOTGUN_01.data();
        shotgun->type = WeaponData::Type::Gun;
        shotgun->coins = 25u;
        shotgun->attackTimeOut = 800.0f;
        shotgun->damage = 80.0f;
        shotgun->range = 550.0f;
        shotgun->attackSoundRef = Asset::Audio::GUN_SHOTGUN.data();

        WeaponSO::add(shotgun);
    }

    //machine pistol
    {
        WeaponData* machine = new WeaponData;

        machine->id = weapons.size();
        machine->name = "Machine Pistol";
        machine->textureRef = Asset::Graphics::MASHINE_PISTOL_01.data();
        machine->type = WeaponData::Type::Gun;
        machine->coins = 20u;
        machine->attackTimeOut = 150.0f;
        machine->damage = 5.0f;
        machine->range = 650.0f;
        machine->attackSoundRef = Asset::Audio::GUN_MACHINE.data();

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

void EntitySO::getStats(const EntityData::Attribute& attribute, float& health, float& strength, const uint& level)
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


    //lvl
    health += (level * 10.f);
    strength += (level * 5.0f);
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
        zombie->level = 3u + zombie->id;
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
        zombieGreen->level = 4u + zombieGreen->id;
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
        zombieShort->level = 2u + zombieShort->id;
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
        zombieSmall->level = 1u + zombieSmall->id;
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
        zombieTall->level = 5u + zombieTall->id;
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
        skeleton->textureRef = Asset::Graphics::ZOMBIE_SKELET.data();

        skeleton->type = EntityData::Type::Basic;
        skeleton->attribute = EntityData::Attribute::LightAssasin;
        skeleton->level = 5u + skeleton->id;
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
        orc->level = 2u + orc->id;
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
        orcArmored->level = 3u + orcArmored->id;
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
        orcMasked->level = 3u + orcMasked->id;
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
        orcShaman->level = 1u + orcShaman->id;
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
        orcVeteran->level = 3u + orcVeteran->id;
        orcVeteran->weaponID = 3u;
        orcVeteran->walkSpeed = 2.8f;
        orcVeteran->runSpeed = 5.5f;
        orcVeteran->scale = 2.3f;

        EntitySO::add(orcVeteran);
    }

    //elemental air
    {
        EntityData* elementalAir = new EntityData;

        elementalAir->id = entities.size();
        elementalAir->name = "Air Elemental";
        elementalAir->textureRef = Asset::Graphics::ELEMENTAL_AIR.data();

        elementalAir->type = EntityData::Type::Basic;
        elementalAir->attribute = EntityData::Attribute::LightAssasin;
        elementalAir->level = 1u + elementalAir->id;
        elementalAir->weaponID = 0u;
        elementalAir->walkSpeed = 5.0f;
        elementalAir->runSpeed = 7.0f;
        elementalAir->scale = 2.0f;

        EntitySO::add(elementalAir);
    }

    //elemental gold short
    {
        EntityData* elementalGoldShort = new EntityData;

        elementalGoldShort->id = entities.size();
        elementalGoldShort->name = "Gold Elemental (Short)";
        elementalGoldShort->textureRef = Asset::Graphics::ELEMENTAL_GOLD_SHORT.data();

        elementalGoldShort->type = EntityData::Type::Basic;
        elementalGoldShort->attribute = EntityData::Attribute::Medium;
        elementalGoldShort->level = 2u + elementalGoldShort->id;
        elementalGoldShort->weaponID = 0u;
        elementalGoldShort->walkSpeed = 2.5f;
        elementalGoldShort->runSpeed = 4.0f;
        elementalGoldShort->scale = 1.8f;

        EntitySO::add(elementalGoldShort);
    }

    //elemental gold tall
    {
        EntityData* elementalGoldTall = new EntityData;

        elementalGoldTall->id = entities.size();
        elementalGoldTall->name = "Gold Elemental (Tall)";
        elementalGoldTall->textureRef = Asset::Graphics::ELEMENTAL_GOLD_TALL.data();

        elementalGoldTall->type = EntityData::Type::Basic;
        elementalGoldTall->attribute = EntityData::Attribute::HeavyTank;
        elementalGoldTall->level = 3u + elementalGoldTall->id;
        elementalGoldTall->weaponID = 2u;
        elementalGoldTall->walkSpeed = 1.0f;
        elementalGoldTall->runSpeed = 2.2f;
        elementalGoldTall->scale = 2.2f;

        EntitySO::add(elementalGoldTall);
    }

    //elemental goo
    {
        EntityData* elementalGoo = new EntityData;

        elementalGoo->id = entities.size();
        elementalGoo->name = "Goo Elemental";
        elementalGoo->textureRef = Asset::Graphics::ELEMENTAL_GOO.data();

        elementalGoo->type = EntityData::Type::Basic;
        elementalGoo->attribute = EntityData::Attribute::Tank;
        elementalGoo->level = 2u + elementalGoo->id;
        elementalGoo->weaponID = 0u;
        elementalGoo->walkSpeed = 1.2f;
        elementalGoo->runSpeed = 2.0f;
        elementalGoo->scale = 2.0f;

        EntitySO::add(elementalGoo);
    }

    //elemental goo small
    {
        EntityData* elementalGooSmall = new EntityData;

        elementalGooSmall->id = entities.size();
        elementalGooSmall->name = "Goo Elemental (Small)";
        elementalGooSmall->textureRef = Asset::Graphics::ELEMENTAL_GOO_SMALL.data();

        elementalGooSmall->type = EntityData::Type::Basic;
        elementalGooSmall->attribute = EntityData::Attribute::Assasin;
        elementalGooSmall->level = 1u + elementalGooSmall->id;
        elementalGooSmall->weaponID = 0u;
        elementalGooSmall->walkSpeed = 2.5f;
        elementalGooSmall->runSpeed = 5.5f;
        elementalGooSmall->scale = 1.5f;

        EntitySO::add(elementalGooSmall);
    }

    //elemental plant
    {
        EntityData* elementalPlant = new EntityData;

        elementalPlant->id = entities.size();
        elementalPlant->name = "Plant Elemental";
        elementalPlant->textureRef = Asset::Graphics::ELEMENTAL_PLANT.data();

        elementalPlant->type = EntityData::Type::Basic;
        elementalPlant->attribute = EntityData::Attribute::Medium;
        elementalPlant->level = 2u + elementalPlant->id;
        elementalPlant->weaponID = 4u;
        elementalPlant->walkSpeed = 1.5f;
        elementalPlant->runSpeed = 3.0f;
        elementalPlant->scale = 2.0f;

        EntitySO::add(elementalPlant);
    }

    //elemental plant small
    {
        EntityData* elementalPlantSmall = new EntityData;

        elementalPlantSmall->id = entities.size();
        elementalPlantSmall->name = "Plant Elemental (Small)";
        elementalPlantSmall->textureRef = Asset::Graphics::ELEMENTAL_PLANT_SMALL.data();

        elementalPlantSmall->type = EntityData::Type::Basic;
        elementalPlantSmall->attribute = EntityData::Attribute::LightAssasin;
        elementalPlantSmall->level = 1u + elementalPlantSmall->id;
        elementalPlantSmall->weaponID = 0u;
        elementalPlantSmall->walkSpeed = 3.5f;
        elementalPlantSmall->runSpeed = 6.0f;
        elementalPlantSmall->scale = 1.5f;

        EntitySO::add(elementalPlantSmall);
    }

    //monster bies
    {
        EntityData* bies = new EntityData;

        bies->id = entities.size();
        bies->name = "Bies";
        bies->textureRef = Asset::Graphics::MONSTER_BIES.data();

        bies->type = EntityData::Type::Basic;
        bies->attribute = EntityData::Attribute::Tank;
        bies->level = 3u + bies->id;
        bies->weaponID = 3u;
        bies->walkSpeed = 1.0f;
        bies->runSpeed = 2.5f;
        bies->scale = 2.3f;

        EntitySO::add(bies);
    }

    //monster chort
    {
        EntityData* chort = new EntityData;

        chort->id = entities.size();
        chort->name = "Chort";
        chort->textureRef = Asset::Graphics::MONSTER_CHORT.data();

        chort->type = EntityData::Type::Basic;
        chort->attribute = EntityData::Attribute::Assasin;
        chort->level = 2u + chort->id;
        chort->weaponID = 1u;
        chort->walkSpeed = 3.0f;
        chort->runSpeed = 5.0f;
        chort->scale = 2.0f;

        EntitySO::add(chort);
    }

    //monster dark knight
    {
        EntityData* darkKnight = new EntityData;

        darkKnight->id = entities.size();
        darkKnight->name = "Dark Knight";
        darkKnight->textureRef = Asset::Graphics::MONSTER_DARK_KNIGHT.data();

        darkKnight->type = EntityData::Type::Basic;
        darkKnight->attribute = EntityData::Attribute::HeavyTank;
        darkKnight->level = 5u + darkKnight->id;
        darkKnight->weaponID = 3u;
        darkKnight->walkSpeed = 0.7f;
        darkKnight->runSpeed = 2.0f;
        darkKnight->scale = 2.5f;

        EntitySO::add(darkKnight);
    }

    //monster demonolog
    {
        EntityData* demonolog = new EntityData;

        demonolog->id = entities.size();
        demonolog->name = "Demonolog";
        demonolog->textureRef = Asset::Graphics::MONSTER_DEMONOLOG.data();

        demonolog->type = EntityData::Type::Basic;
        demonolog->attribute = EntityData::Attribute::Medium;
        demonolog->level = 3u + demonolog->id;
        demonolog->weaponID = 4u;
        demonolog->walkSpeed = 1.5f;
        demonolog->runSpeed = 3.5f;
        demonolog->scale = 2.2f;

        EntitySO::add(demonolog);
    }

    //monster rokita
    {
        EntityData* rokita = new EntityData;

        rokita->id = entities.size();
        rokita->name = "Rokita";
        rokita->textureRef = Asset::Graphics::MONSTER_ROKITA.data();

        rokita->type = EntityData::Type::Basic;
        rokita->attribute = EntityData::Attribute::Assasin;
        rokita->level = 2u + rokita->id;
        rokita->weaponID = 1u;
        rokita->walkSpeed = 4.0f;
        rokita->runSpeed = 6.5f;
        rokita->scale = 1.9f;

        EntitySO::add(rokita);
    }

    //monster wogolo
    {
        EntityData* wogolo = new EntityData;

        wogolo->id = entities.size();
        wogolo->name = "Wogolo";
        wogolo->textureRef = Asset::Graphics::MONSTER_WOGOLO.data();

        wogolo->type = EntityData::Type::Basic;
        wogolo->attribute = EntityData::Attribute::Medium;
        wogolo->level = 3u + wogolo->id;
        wogolo->weaponID = 2u;
        wogolo->walkSpeed = 2.2f;
        wogolo->runSpeed = 4.5f;
        wogolo->scale = 2.6f;

        EntitySO::add(wogolo);
    }

    //monster necromancer
    {
        EntityData* necromancer = new EntityData;

        necromancer->id = entities.size();
        necromancer->name = "Necromancer";
        necromancer->textureRef = Asset::Graphics::MONSTER_NECROMANCER.data();

        necromancer->type = EntityData::Type::Basic;
        necromancer->attribute = EntityData::Attribute::Medium;
        necromancer->level = 4u + necromancer->id;
        necromancer->weaponID = 4u;
        necromancer->walkSpeed = 1.7f;
        necromancer->runSpeed = 3.8f;
        necromancer->scale = 2.3f;

        EntitySO::add(necromancer);
    }

    //monster imp
    {
        EntityData* imp = new EntityData;

        imp->id = entities.size();
        imp->name = "Imp";
        imp->textureRef = Asset::Graphics::MONSTER_IMP.data();

        imp->type = EntityData::Type::Basic;
        imp->attribute = EntityData::Attribute::LightAssasin;
        imp->level = 1u + imp->id;
        imp->weaponID = 0u;
        imp->walkSpeed = 4.0f;
        imp->runSpeed = 7.0f;
        imp->scale = 1.2f;

        EntitySO::add(imp);
    }

    //monster goblin
    {
        EntityData* goblin = new EntityData;

        goblin->id = entities.size();
        goblin->name = "Goblin";
        goblin->textureRef = Asset::Graphics::MONSTER_GOBLIN.data();

        goblin->type = EntityData::Type::Basic;
        goblin->attribute = EntityData::Attribute::Assasin;
        goblin->level = 2u + goblin->id;
        goblin->weaponID = 0u;
        goblin->walkSpeed = 3.2f;
        goblin->runSpeed = 8.0f;
        goblin->scale = 1.5f;

        EntitySO::add(goblin);
    }
}

