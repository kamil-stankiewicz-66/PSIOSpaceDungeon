#include "game/core/Parameter.h"


float Parameters::player_moveSpeed = 8.0f;

int Parameters::levelGenerator_levelNumberMultiplier = 5;
int Parameters::levelGenerator_roomsNumber_min = 40;
int Parameters::levelGenerator_roomsNumber_max = 50;
int Parameters::levelGenerator_corridorLength_min = 8;
int Parameters::levelGenerator_corridorLength_max = 15;
int Parameters::levelGenerator_enemiesFrequency = 3;


///
/// player
///

const float& Parameters::get_player_moveSpeed() {
    return player_moveSpeed;
}


///
/// generator
///

const int& Parameters::get_levelGenerator_levelNumberMultiplier() {
    return levelGenerator_levelNumberMultiplier;
}


const int& Parameters::get_levelGenerator_roomsNumber_min() {
    return levelGenerator_roomsNumber_min;
}

const int& Parameters::get_levelGenerator_roomsNumber_max() {
    return levelGenerator_roomsNumber_max;
}

const int& Parameters::get_levelGenerator_corridorLength_min() {
    return levelGenerator_corridorLength_min;
}

const int& Parameters::get_levelGenerator_corridorLength_max() {
    return levelGenerator_corridorLength_max;
}

const int& Parameters::get_levelGenerator_enemiesFrequency() {
    return levelGenerator_enemiesFrequency;
}
