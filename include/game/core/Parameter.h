#ifndef PARAMETER_H
#define PARAMETER_H

struct Parameters
{
    friend class Game;


    static float player_moveSpeed;
    static float player_baseHealth;
    static float player_regenerationRate;
    static int player_progressExp;

    static float camera_viewSize;
    static float camera_trackingOn;
    static float camera_trackingOff;
    static float camera_speed;

    static int levelGenerator_levelNumberMultiplier;
    static int levelGenerator_roomsNumber_min;
    static int levelGenerator_roomsNumber_max;
    static int levelGenerator_roomSize_min;
    static int levelGenerator_roomSize_max;
    static int levelGenerator_corridorLength_min;
    static int levelGenerator_corridorLength_max;
    static int levelGenerator_corridor_width;
    static float levelGenerator_enemiesFrequency;
    static float levelGenerator_chestsFrequency;
    static int levelGenerator_chestsCoinsMultiplier;

    static float bullet_speed;

    static float entity_rndMoveIntense;
    static float entity_heavyTank_health;
    static float entity_heavyTank_strength;
    static float entity_tank_health;
    static float entity_tank_strength;
    static float entity_medium_health;
    static float entity_medium_strength;
    static float entity_assasin_health;
    static float entity_assasin_strength;
    static float entity_lightAssasin_health;
    static float entity_lightAssasin_strength;



public:

    //init method
    static void init();


    //getters

    static const float& get_player_moveSpeed();
    static const float& get_player_baseHealth();
    static const float& get_player_regenerationRate();
    static const int& get_player_progressExp();    

    static const float& get_camera_viewSize();
    static const float& get_camera_trackingOn();
    static const float& get_camera_trackingOff();
    static const float& get_camera_speed();

    static const int& get_levelGenerator_levelNumberMultiplier();
    static const int& get_levelGenerator_roomsNumber_min();
    static const int& get_levelGenerator_roomsNumber_max();
    static const int& get_levelGenerator_roomSize_min();
    static const int& get_levelGenerator_roomSize_max();
    static const int& get_levelGenerator_corridorLength_min();
    static const int& get_levelGenerator_corridorLength_max();
    static const int& get_levelGenerator_corridor_width();
    static const float& get_levelGenerator_enemiesFrequency();
    static const float& get_levelGenerator_chestsFrequency();
    static const int& get_levelGenerator_chestsCoinsMultiplier();

    static const float& get_bullet_speed();

    static const float& get_entity_rndMoveIntense();
    static const float& get_entity_heavyTank_health();
    static const float& get_entity_heavyTank_strength();
    static const float& get_entity_tank_health();
    static const float& get_entity_tank_strength();
    static const float& get_entity_medium_health();
    static const float& get_entity_medium_strength();
    static const float& get_entity_assasin_health();
    static const float& get_entity_assasin_strength();
    static const float& get_entity_lightAssasin_health();
    static const float& get_entity_lightAssasin_strength();

};

#endif // PARAMETER_H
