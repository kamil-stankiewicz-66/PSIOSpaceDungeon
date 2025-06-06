#include "game/core/Parameter.h"


float Parameters::player_moveSpeed = 8.0f;

float Parameters::camera_viewSize = 1.2f;
float Parameters::camera_trackingOn = 120.0f;
float Parameters::camera_trackingOff = 5.0f;
float Parameters::camera_speed = 12.0f;

int Parameters::levelGenerator_levelNumberMultiplier = 5;
int Parameters::levelGenerator_roomsNumber_min = 5;
int Parameters::levelGenerator_roomsNumber_max = 10;
int Parameters::levelGenerator_roomSize_min = 14;
int Parameters::levelGenerator_roomSize_max = 20;
int Parameters::levelGenerator_corridorLength_min = 3;
int Parameters::levelGenerator_corridorLength_max = 8;
int Parameters::levelGenerator_corridor_width = 5;
int Parameters::levelGenerator_enemiesFrequency = 3;

float Parameters::bullet_speed = 30.0f;



///
/// init
///

void Parameters::init()
{
    Parameters::player_moveSpeed = 8.0f;

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
    Parameters::levelGenerator_enemiesFrequency = 3;

    Parameters::bullet_speed = 30.0f;
}




///
/// player
///

const float& Parameters::get_player_moveSpeed() {
    return player_moveSpeed;
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

const int& Parameters::get_levelGenerator_enemiesFrequency() {
    return levelGenerator_enemiesFrequency;
}


///
/// weapons
///

const float& Parameters::get_bullet_speed() {
    return bullet_speed;
}
