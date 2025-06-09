#ifndef DATABLOCKS_H
#define DATABLOCKS_H

#include <string_view>
using uint = unsigned int;


///
/// \brief File paths.
///

struct FilePath
{
    static constexpr std::string_view PLAYER_DATA = "playerdata.save";
};


///
/// \brief Static player data class.
/// \details stores player data and passes it between scenes
///

class PlayerData
{
private:
    static uint exp_points;
    static uint weapon_id;
    static uint coins;

public:

    //setters
    static void setExpPoints(const uint&);
    static void setWeaponID(const uint&);
    static void setCoins(const uint&);

    //getters
    static uint getExpPoints();
    static uint getWeaponID();
    static uint getCoins();
    static uint getExpLevel();
    static float getMaxHealth();
    static uint getDamage();
};

/// [serializable]
#pragma pack(push, 1)
struct SPlayerData
{
    uint exp_points = 0u;
    uint weapon_id = 1u;
    uint coins = 0u;
};
#pragma pack(pop)

#endif // DATABLOCKS_H
