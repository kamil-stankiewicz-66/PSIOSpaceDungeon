#ifndef DATABLOCKS_H
#define DATABLOCKS_H

using uint = unsigned int;

struct LevelData
{
    static uint level_nr;
};

struct PlayerData
{
    static uint exp_points;
    static uint weapon_id;
    static uint coins;
};

#endif // DATABLOCKS_H
