#ifndef DATABLOCKS_H
#define DATABLOCKS_H

using uint = unsigned int;


///
/// \brief Static level data struct.
/// \details Stores level data and passes it between scenes
///

struct LevelData
{
    static uint level_nr;
};


/// [serializable]
struct SLevelData
{
    uint level_nr;
};



///
/// \brief Static player data class.
/// \details stores player data and passes it between scenes
///

struct PlayerData
{
    static uint exp_points;
    static uint weapon_id;
    static uint coins;
};


/// [serializable]
struct SPlayerData
{
    uint exp_points;
    uint weapon_id;
    uint coins;
};

#endif // DATABLOCKS_H
