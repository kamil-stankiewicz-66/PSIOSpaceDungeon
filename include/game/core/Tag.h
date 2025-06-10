#ifndef TAG_H
#define TAG_H

#include <string_view>

struct Tag
{
    //player
    static constexpr std::string_view PLAYER_CORE = "Player";
    static constexpr std::string_view PLAYER_BODY = "PlayerBody";
    static constexpr std::string_view PLAYER_RECT = "PlayerRect";
    static constexpr std::string_view PLAYER_CAPE = "PlayerCape";
    static constexpr std::string_view PLAYER_LEG_LEFT = "PlayerLegLeft";
    static constexpr std::string_view PLAYER_LEG_RIGHT = "PlayerLegRight";
    static constexpr std::string_view PLAYER_HEALTH_BAR = "PlayerHealthBar";
    static constexpr std::string_view PLAYER_HEAL_BAR = "PlayerHealBar";

    //tilemaps
    static constexpr std::string_view TILEMAP = "tilemap";
    static constexpr std::string_view TILEMAP_BG = "bg_tilemap";
    static constexpr std::string_view TILEMAP_FG = "fg_tilemap";

    //entity
    static constexpr std::string_view ENEMY = "enemy";
};

#endif // TAG_H
