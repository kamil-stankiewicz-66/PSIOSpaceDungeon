#include "game/core/DataBlock.h"
#include "game/core/Parameter.h"
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


uint PlayerData::getExpPoints() {
    return exp_points;
}

unsigned int PlayerData::getWeaponID() {
    return weapon_id;
}



unsigned int PlayerData::getCoins() {
    return coins;
}

uint PlayerData::getExpLevel() {
    return 1u + (exp_points / Parameters::get_player_progressExp());
}

float PlayerData::getMaxHealth() {
    return Parameters::get_player_baseHealth() + (static_cast<float>(getExpLevel()) * Parameters::get_player_baseHealth() * 0.1f);
}

uint PlayerData::getDamage() {
    return 1 + static_cast<uint>(floor(getExpLevel() * 0.5f));
}
