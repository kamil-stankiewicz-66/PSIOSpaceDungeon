#include "game/core/Parameter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

float Parameters::player_moveSpeed;
float Parameters::player_baseHealth;
float Parameters::player_regenerationRate;
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

int Parameters::exp_perEnemyKill;
float Parameters::exp_bonusLevelCompleteMultiplier;

float Parameters::sound_volume_effects;
float Parameters::sound_volume_music;




///
/// init
///


void Parameters::init()
{
    Parameters::player_moveSpeed = 8.0f;
    Parameters::player_baseHealth = 500.0f;
    Parameters::player_regenerationRate = 0.005f;
    Parameters::player_progressExp = 1000;

    Parameters::camera_viewSize = 1.2f;
    Parameters::camera_trackingOn = 120.0f;
    Parameters::camera_trackingOff = 5.0f;
    Parameters::camera_speed = 12.0f;

    Parameters::levelGenerator_levelNumberMultiplier = 5;
    Parameters::levelGenerator_roomsNumber_min = 6;
    Parameters::levelGenerator_roomsNumber_max = 15;
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
    Parameters::entity_heavyTank_strength = 200.0f;
    Parameters::entity_tank_health = 120.0f;
    Parameters::entity_tank_strength = 120.0f;
    Parameters::entity_medium_health = 100.0f;
    Parameters::entity_medium_strength = 80.0f;
    Parameters::entity_assasin_health = 50.0f;
    Parameters::entity_assasin_strength = 70.0f;
    Parameters::entity_lightAssasin_health = 15.0f;
    Parameters::entity_lightAssasin_strength = 60.0f;

    Parameters::exp_perEnemyKill = 5;
    Parameters::exp_bonusLevelCompleteMultiplier = 3;

    Parameters::sound_volume_effects = 100.0f;
    Parameters::sound_volume_music = 20.0f;
}

void Parameters::initFromTxt(const std::string& filename)
{
    init();

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "[Parameters] Nie mozna otworzyc pliku: " << filename << '\n';
        return;
    }

    std::unordered_map<std::string, std::string> raw;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        std::string key, eq, val;
        if (iss >> key >> eq >> val && eq == "=")
            raw[key] = val;
    }

    auto strip_f = [](std::string& v) {
        if (!v.empty() && (v.back() == 'f' || v.back() == 'F'))
            v.pop_back();
    };


    const std::unordered_map<std::string, float*> floatMap{
        { "player_moveSpeed", &player_moveSpeed },
        { "player_baseHealth", &player_baseHealth },
        { "player_regenerationRate", &player_regenerationRate },

        { "camera_viewSize", &camera_viewSize },
        { "camera_trackingOn", &camera_trackingOn },
        { "camera_trackingOff", &camera_trackingOff },
        { "camera_speed", &camera_speed },

        { "levelGenerator_enemiesFrequency", &levelGenerator_enemiesFrequency },
        { "levelGenerator_chestsFrequency", &levelGenerator_chestsFrequency },

        { "bullet_speed", &bullet_speed },

        { "entity_rndMoveIntense", &entity_rndMoveIntense },
        { "entity_heavyTank_health", &entity_heavyTank_health },
        { "entity_heavyTank_strength", &entity_heavyTank_strength },
        { "entity_tank_health", &entity_tank_health },
        { "entity_tank_strength", &entity_tank_strength },
        { "entity_medium_health", &entity_medium_health },
        { "entity_medium_strength", &entity_medium_strength },
        { "entity_assasin_health", &entity_assasin_health },
        { "entity_assasin_strength", &entity_assasin_strength },
        { "entity_lightAssasin_health", &entity_lightAssasin_health },
        { "entity_lightAssasin_strength", &entity_lightAssasin_strength },

        { "exp_bonusLevelCompleteMultiplier", &exp_bonusLevelCompleteMultiplier },

        { "sound_volume_effects", &sound_volume_effects },
        { "sound_volume_music", &sound_volume_music }
    };

    const std::unordered_map<std::string, int*> intMap{
        { "player_progressExp", &player_progressExp },

        { "levelGenerator_levelNumberMultiplier", &levelGenerator_levelNumberMultiplier },
        { "levelGenerator_roomsNumber_min", &levelGenerator_roomsNumber_min },
        { "levelGenerator_roomsNumber_max", &levelGenerator_roomsNumber_max },
        { "levelGenerator_roomSize_min", &levelGenerator_roomSize_min },
        { "levelGenerator_roomSize_max", &levelGenerator_roomSize_max },
        { "levelGenerator_corridorLength_min", &levelGenerator_corridorLength_min },
        { "levelGenerator_corridorLength_max", &levelGenerator_corridorLength_max },
        { "levelGenerator_corridor_width", &levelGenerator_corridor_width },
        { "levelGenerator_chestsCoinsMultiplier", &levelGenerator_chestsCoinsMultiplier },

        { "exp_perEnemyKill", &exp_perEnemyKill }
    };


    for (const auto& [key, ptr] : floatMap)
    {
        if (auto it = raw.find(key); it != raw.end())
        {
            std::string val = it->second;
            strip_f(val);
            try { *ptr = std::stof(val); }
            catch (...) { std::cerr << "[Parameters] Błąd konwersji float: " << key << '\n'; }
        }
    }

    for (const auto& [key, ptr] : intMap)
    {
        if (auto it = raw.find(key); it != raw.end())
        {
            std::string val = it->second;
            strip_f(val);
            try { *ptr = std::stoi(val); }
            catch (...) { std::cerr << "[Parameters] Błąd konwersji int: " << key << '\n'; }
        }
    }
}



///
/// player
///

const float& Parameters::get_player_moveSpeed() {
    return player_moveSpeed;
}

const float& Parameters::get_player_baseHealth() {
    return player_baseHealth;
}

const float& Parameters::get_player_regenerationRate() {
    return player_regenerationRate;
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


///
/// exp
///

const int& Parameters::get_exp_perEnemyKill() {
    return exp_perEnemyKill;
}

const float& Parameters::get_exp_bonusLevelCompleteMultiplier() {
    return exp_bonusLevelCompleteMultiplier;
}


///
/// sound
///

const float& Parameters::get_sound_volume_effects() {
    return sound_volume_effects;
}

const float& Parameters::get_sound_volume_music() {
    return sound_volume_music;
}
