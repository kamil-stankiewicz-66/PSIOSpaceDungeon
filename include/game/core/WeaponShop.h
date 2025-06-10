#ifndef WEAPONSHOP_H
#define WEAPONSHOP_H

#include "engine/object/Object.h"
#include "game/core/ScriptableObject.h"
#include "game/entity/Weapon.h"

class WeaponShop : public Object
{
private:
    vector<const WeaponData*> availableWeapons;
    Scene* scene;
    uint playerCoins;
    string targetTag;

public:
    WeaponShop(Scene* scene, const string& targetTag, uint coins = 100);

    void display();
    void buyWeapon(uint weaponID);

    void setCoins(uint coins);
    uint getCoins() const;
};

#endif // WEAPONSHOP_H
