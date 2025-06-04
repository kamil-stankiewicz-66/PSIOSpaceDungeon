#ifndef PARAMETER_H
#define PARAMETER_H

struct Parameters
{
private:
    static float player_moveSpeed;

    static int levelGenerator_levelNumberMultiplier;
    static int levelGenerator_roomsNumber_min;
    static int levelGenerator_roomsNumber_max;
    static int levelGenerator_roomSize_min;
    static int levelGenerator_roomSize_max;
    static int levelGenerator_corridorLength_min;
    static int levelGenerator_corridorLength_max;
    static int levelGenerator_corridor_width;
    static int levelGenerator_enemiesFrequency;

public:
    static const float& get_player_moveSpeed();

    static const int& get_levelGenerator_levelNumberMultiplier();
    static const int& get_levelGenerator_roomsNumber_min();
    static const int& get_levelGenerator_roomsNumber_max();
    static const int& get_levelGenerator_roomSize_min();
    static const int& get_levelGenerator_roomSize_max();
    static const int& get_levelGenerator_corridorLength_min();
    static const int& get_levelGenerator_corridorLength_max();
    static const int& get_levelGenerator_corridor_width();
    static const int& get_levelGenerator_enemiesFrequency();
};

#endif // PARAMETER_H
