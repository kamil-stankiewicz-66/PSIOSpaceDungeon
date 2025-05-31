#ifndef ASSET_H
#define ASSET_H

#include <string_view>

struct Asset
{
    struct Graphics
    {
        //chest
        static constexpr std::string_view CHEST_CLOSED = "Graphics/Chest/chest_closed.png";
        static constexpr std::string_view CHEST_GOLDEN_CLOSED = "Graphics/Chest/chest_golden_closed.png";
        static constexpr std::string_view CHEST_GOLDEN_OPEN_EMPTY = "Graphics/Chest/chest_golden_open_empty.png";
        static constexpr std::string_view CHEST_GOLDEN_OPEN_FULL = "Graphics/Chest/chest_golden_open_full.png";
        static constexpr std::string_view CHEST_OPEN_EMPTY = "Graphics/Chest/chest_open_empty.png";
        static constexpr std::string_view CHEST_OPEN_FULL = "Graphics/Chest/chest_open_full.png";

        //entities
        static constexpr std::string_view HEALTHBAR = "Graphics/Entities/HealthBar.png";

        //orcs
        static constexpr std::string_view ORC_ARMORED = "Graphics/Entities/orcs/armored.png";
        static constexpr std::string_view ORC_BASIC = "Graphics/Entities/orcs/orc.png";
        static constexpr std::string_view ORC_MASKED = "Graphics/Entities/orcs/orc_masked.png";
        static constexpr std::string_view ORC_SHAMAN = "Graphics/Entities/orcs/orc_shaman.png";
        static constexpr std::string_view ORC_VETERAN = "Graphics/Entities/orcs/orc_veteran.png";

        //zombies
        static constexpr std::string_view ZOMBIE_SKELETON = "Graphics/Entities/zombies/monster_skelet.png";
        static constexpr std::string_view ZOMBIE_BASIC = "Graphics/Entities/zombies/monster_zombie.png";
        static constexpr std::string_view ZOMBIE_GREEN = "Graphics/Entities/zombies/monster_zombie_green.png";
        static constexpr std::string_view ZOMBIE_SHORT = "Graphics/Entities/zombies/monster_zombie_short.png";
        static constexpr std::string_view ZOMBIE_SMALL = "Graphics/Entities/zombies/monster_zombie_small.png";
        static constexpr std::string_view ZOMBIE_TALL = "Graphics/Entities/zombies/monster_zombie_tall.png";

        //GUI
        static constexpr std::string_view LEFTRIGHT_ARROWS = "Graphics/GUI/leftRightArrows.png";

        //particles
        static constexpr std::string_view PARTICLE = "Graphics/Particles/particle.png";

        //player
        static constexpr std::string_view CAPE_BASE = "Graphics/Player/cape_base.png";
        static constexpr std::string_view PLAYER_SKIN_01 = "Graphics/Player/player_skin_01.png";
        static constexpr std::string_view PLAYER_SKIN_02 = "Graphics/Player/player_skin_02.png";

        //tilesets
        static constexpr std::string_view BOXES = "Graphics/Tilesets/boxes.png";
        static constexpr std::string_view COLUMNS = "Graphics/Tilesets/columns.png";
        static constexpr std::string_view DOOR = "Graphics/Tilesets/door.png";
        static constexpr std::string_view EMPTY = "Graphics/Tilesets/empty.png";
        static constexpr std::string_view FLOOR_LADDER = "Graphics/Tilesets/floor_ladder.png";
        static constexpr std::string_view FLOOR_LIGHT = "Graphics/Tilesets/floor_light.png";
        static constexpr std::string_view FLOOR_MAIN = "Graphics/Tilesets/floor_main.png";
        static constexpr std::string_view FLOOR_PLATES = "Graphics/Tilesets/floor_plates.png";
        static constexpr std::string_view GARGOYLES = "Graphics/Tilesets/gargoyles.png";
        static constexpr std::string_view HOLE = "Graphics/Tilesets/hole.png";
        static constexpr std::string_view SKULL_01 = "Graphics/Tilesets/skull_01.png";
        static constexpr std::string_view STAIRS = "Graphics/Tilesets/stairs.png";
        static constexpr std::string_view WALL_BROKEN = "Graphics/Tilesets/wall_broken.png";
        static constexpr std::string_view WALL_CLOSED = "Graphics/Tilesets/wall_closed.png";
        static constexpr std::string_view WALL_CRATES = "Graphics/Tilesets/wall_crates.png";
        static constexpr std::string_view WALL_FLAGS = "Graphics/Tilesets/wall_flags.png";
        static constexpr std::string_view WALL_MAIN = "Graphics/Tilesets/wall_main.png";
        static constexpr std::string_view WALL_PIPES = "Graphics/Tilesets/wall_pipes.png";
        static constexpr std::string_view WALL_SLIME = "Graphics/Tilesets/wall_slime.png";

        //weapons
        static constexpr std::string_view LASER_BULLET = "Graphics/Weapons/laser_bullet.png";
        static constexpr std::string_view ASSAULT_RIFLE_01 = "Graphics/Weapons/Guns/assault_rifle_01.png";
        static constexpr std::string_view ASSAULT_RIFLE_01_SHOP = "Graphics/Weapons/Guns/assault_rifle_01_shop.png";
    };
};

#endif // ASSET_H
