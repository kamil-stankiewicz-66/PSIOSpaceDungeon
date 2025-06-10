#include "game/core/Parameter.h"


float Parameters::player_moveSpeed;
int Parameters::player_progressExp;

float Parameters::camera_viewSize;
float Parameters::camera_trackingOn;
float Parameters::camera_trackingOff;
float Parameters::camera_speed;

int Parameters::levelGenerator_levelNumberMultiplier;
int Parameters::levelGenerator_roomsNumber_min;
int Parameters::levelGenerator_roomsNumber_max;
int Parameters::levelGenerator_roomSize_min;
int Parameters::levelGenerator_roomSize_max;
int Parameters::levelGenerator_corridorLength_min;
int Parameters::levelGenerator_corridorLength_max;
int Parameters::levelGenerator_corridor_width;
float Parameters::levelGenerator_enemiesFrequency;
float Parameters::levelGenerator_chestsFrequency;
int Parameters::levelGenerator_chestsCoinsMultiplier;

float Parameters::bullet_speed;

float Parameters::entity_rndMoveIntense;
float Parameters::entity_heavyTank_health;
float Parameters::entity_heavyTank_strength;
float Parameters::entity_tank_health;
float Parameters::entity_tank_strength;
float Parameters::entity_medium_health;
float Parameters::entity_medium_strength;
float Parameters::entity_assasin_health;
float Parameters::entity_assasin_strength;
float Parameters::entity_lightAssasin_health;
float Parameters::entity_lightAssasin_strength;




///
/// init
///

void Parameters::init()
{
    Parameters::player_moveSpeed = 8.0f;
    Parameters::player_progressExp = 1000;

    Parameters::camera_viewSize = 1.2f;
    Parameters::camera_trackingOn = 120.0f;
    Parameters::camera_trackingOff = 5.0f;
    Parameters::camera_speed = 12.0f;

    Parameters::levelGenerator_levelNumberMultiplier = 5;
    Parameters::levelGenerator_roomsNumber_min = 5;
    Parameters::levelGenerator_roomsNumber_max = 10;
    Parameters::levelGenerator_roomSize_min = 14;
    Parameters::levelGenerator_roomSize_max = 20;
    Parameters::levelGenerator_corridorLength_min = 3;
    Parameters::levelGenerator_corridorLength_max = 8;
    Parameters::levelGenerator_corridor_width = 5;
    Parameters::levelGenerator_enemiesFrequency = 0.05f;
    Parameters::levelGenerator_chestsFrequency = 0.05f;
    Parameters::levelGenerator_chestsCoinsMultiplier = 3;

    Parameters::bullet_speed = 30.0f;

    Parameters::entity_rndMoveIntense = 4000.0f;
    Parameters::entity_heavyTank_health = 200.0f;
    Parameters::entity_heavyTank_strength = 150.0f;
    Parameters::entity_tank_health = 120.0f;
    Parameters::entity_tank_strength = 80.0f;
    Parameters::entity_medium_health = 100.0f;
    Parameters::entity_medium_strength = 40.0f;
    Parameters::entity_assasin_health = 50.0f;
    Parameters::entity_assasin_strength = 30.0f;
    Parameters::entity_lightAssasin_health = 15.0f;
    Parameters::entity_lightAssasin_strength = 40.0f;
}




///
/// player
///

const float& Parameters::get_player_moveSpeed() {
    return player_moveSpeed;
}

const int& Parameters::get_player_progressExp() {
    return player_progressExp;
}


///
/// camera
///

const float& Parameters::get_camera_viewSize() {
    return camera_viewSize;
}

const float& Parameters::get_camera_trackingOn() {
    return camera_trackingOn;
}

const float& Parameters::get_camera_trackingOff() {
    return camera_trackingOff;
}

const float& Parameters::get_camera_speed() {
    return camera_speed;
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

const int& Parameters::get_levelGenerator_roomSize_min() {
    return levelGenerator_roomSize_min;
}

const int& Parameters::get_levelGenerator_roomSize_max() {
    return levelGenerator_roomSize_max;
}

const int& Parameters::get_levelGenerator_corridorLength_min() {
    return levelGenerator_corridorLength_min;
}

const int& Parameters::get_levelGenerator_corridorLength_max() {
    return levelGenerator_corridorLength_max;
}

const int& Parameters::get_levelGenerator_corridor_width() {
    return levelGenerator_corridor_width;
}

const float& Parameters::get_levelGenerator_enemiesFrequency() {
    return levelGenerator_enemiesFrequency;
}

const float& Parameters::get_levelGenerator_chestsFrequency() {
    return levelGenerator_chestsFrequency;
}

const int& Parameters::get_levelGenerator_chestsCoinsMultiplier() {
    return levelGenerator_chestsCoinsMultiplier;
}


///
/// weapons
///

const float& Parameters::get_bullet_speed() {
    return bullet_speed;
}


///
/// entity
///

const float& Parameters::get_entity_rndMoveIntense() {
    return entity_rndMoveIntense;
}

const float& Parameters::get_entity_heavyTank_health() {
    return entity_heavyTank_health;
}

const float& Parameters::get_entity_heavyTank_strength() {
    return entity_heavyTank_strength;
}

const float& Parameters::get_entity_tank_health() {
    return entity_tank_health;
}

const float& Parameters::get_entity_tank_strength() {
    return entity_tank_strength;
}

const float& Parameters::get_entity_medium_health() {
    return entity_medium_health;
}

const float& Parameters::get_entity_medium_strength() {
    return entity_medium_strength;
}

const float& Parameters::get_entity_assasin_health() {
    return entity_assasin_health;
}

const float& Parameters::get_entity_assasin_strength() {
    return entity_assasin_strength;
}

const float& Parameters::get_entity_lightAssasin_health() {
    return entity_lightAssasin_health;
}

const float& Parameters::get_entity_lightAssasin_strength() {
    return entity_lightAssasin_strength;
}
