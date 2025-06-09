#include "game/core/DataBlock.h"
#include <cmath>

uint PlayerData::exp_points = 0u;
uint PlayerData::weapon_id = 1u;
uint PlayerData::coins = 0u;



void PlayerData::setExpPoints(const unsigned int& value) {
    exp_points = value;
}

void PlayerData::setWeaponID(const unsigned int& value) {
    weapon_id = value;
}

void PlayerData::setCoins(const unsigned int& value) {
    coins = value;
}

unsigned int PlayerData::getExpPoints() {
    return exp_points;
}

unsigned int PlayerData::getWeaponID() {
    return weapon_id;
}



unsigned int PlayerData::getCoins() {
    return coins;
}

uint PlayerData::getExpLevel() {
    return 1u + (exp_points / 1000u);
}

float PlayerData::getMaxHealth() {
    return 100.f + (static_cast<float>(getExpLevel()) * 10.f);
}

uint PlayerData::getDamage() {
    return 2 + static_cast<uint>(floor(getExpLevel() * 0.5f));
}
