#ifndef ASSET_H
#define ASSET_H

#include <string_view>

struct Asset
{
    struct Graphics
    {
        //chest
        static constexpr std::string_view CHEST_CLOSED = "assets/Graphics/Chest/chest_closed.png";
        static constexpr std::string_view CHEST_GOLDEN_CLOSED = "assets/Graphics/Chest/chest_golden_closed.png";
        static constexpr std::string_view CHEST_GOLDEN_OPEN_EMPTY = "assets/Graphics/Chest/chest_golden_open_empty.png";
        static constexpr std::string_view CHEST_GOLDEN_OPEN_FULL = "assets/Graphics/Chest/chest_golden_open_full.png";
        static constexpr std::string_view CHEST_OPEN_EMPTY = "assets/Graphics/Chest/chest_open_empty.png";
        static constexpr std::string_view CHEST_OPEN_FULL = "assets/Graphics/Chest/chest_open_full.png";

        //entities
        static constexpr std::string_view HEALTHBAR = "assets/Graphics/Entities/HealthBar.png";

        //orcs
        static constexpr std::string_view ORC_ARMORED = "assets/Graphics/Entities/orcs/armored.png";
        static constexpr std::string_view ORC_BASIC = "assets/Graphics/Entities/orcs/orc.png";
        static constexpr std::string_view ORC_MASKED = "assets/Graphics/Entities/orcs/orc_masked.png";
        static constexpr std::string_view ORC_SHAMAN = "assets/Graphics/Entities/orcs/orc_shaman.png";
        static constexpr std::string_view ORC_VETERAN = "assets/Graphics/Entities/orcs/orc_veteran.png";

        //zombies
        static constexpr std::string_view ZOMBIE_SKELETON = "assets/Graphics/Entities/zombies/monster_skelet.png";
        static constexpr std::string_view ZOMBIE_BASIC = "assets/Graphics/Entities/zombies/monster_zombie.png";
        static constexpr std::string_view ZOMBIE_GREEN = "assets/Graphics/Entities/zombies/monster_zombie_green.png";
        static constexpr std::string_view ZOMBIE_SHORT = "assets/Graphics/Entities/zombies/monster_zombie_short.png";
        static constexpr std::string_view ZOMBIE_SMALL = "assets/Graphics/Entities/zombies/monster_zombie_small.png";
        static constexpr std::string_view ZOMBIE_TALL = "assets/Graphics/Entities/zombies/monster_zombie_tall.png";

        //GUI
        static constexpr std::string_view LEFTRIGHT_ARROWS = "assets/Graphics/GUI/leftRightArrows.png";
        static constexpr std::string_view BUTTON = "assets/Graphics/GUI/button.png";

        //particles
        static constexpr std::string_view PARTICLE = "assets/Graphics/Particles/particle.png";

        //player
        static constexpr std::string_view CAPE_BASE = "assets/Graphics/Player/cape_base.png";
        static constexpr std::string_view PLAYER_SKIN_01 = "assets/Graphics/Player/player_skin_01.png";
        static constexpr std::string_view PLAYER_SKIN_02 = "assets/Graphics/Player/player_skin_02.png";

        //tilesets
        static constexpr std::string_view BOXES = "assets/Graphics/Tilesets/boxes.png";
        static constexpr std::string_view COLUMNS = "assets/Graphics/Tilesets/columns.png";
        static constexpr std::string_view DOOR = "assets/Graphics/Tilesets/door.png";
        static constexpr std::string_view EMPTY = "assets/Graphics/Tilesets/empty.png";
        static constexpr std::string_view FLOOR_LADDER = "assets/Graphics/Tilesets/floor_ladder.png";
        static constexpr std::string_view FLOOR_LIGHT = "assets/Graphics/Tilesets/floor_light.png";
        static constexpr std::string_view FLOOR_MAIN = "assets/Graphics/Tilesets/floor_main.png";
        static constexpr std::string_view FLOOR_PLATES = "assets/Graphics/Tilesets/floor_plates.png";
        static constexpr std::string_view GARGOYLES = "assets/Graphics/Tilesets/gargoyles.png";
        static constexpr std::string_view HOLE = "assets/Graphics/Tilesets/hole.png";
        static constexpr std::string_view SKULL_01 = "assets/Graphics/Tilesets/skull_01.png";
        static constexpr std::string_view STAIRS = "assets/Graphics/Tilesets/stairs.png";
        static constexpr std::string_view WALL_BROKEN = "assets/Graphics/Tilesets/wall_broken.png";
        static constexpr std::string_view WALL_CLOSED = "assets/Graphics/Tilesets/wall_closed.png";
        static constexpr std::string_view WALL_CRATES = "assets/Graphics/Tilesets/wall_crates.png";
        static constexpr std::string_view WALL_FLAGS = "assets/Graphics/Tilesets/wall_flags.png";
        static constexpr std::string_view WALL_MAIN = "assets/Graphics/Tilesets/wall_main.png";
        static constexpr std::string_view WALL_PIPES = "assets/Graphics/Tilesets/wall_pipes.png";
        static constexpr std::string_view WALL_SLIME = "assets/Graphics/Tilesets/wall_slime.png";

        //weapons
        static constexpr std::string_view LASER_BULLET = "assets/Graphics/Weapons/laser_bullet.png";
        static constexpr std::string_view ASSAULT_RIFLE_01 = "assets/Graphics/Weapons/Guns/assault_rifle_01.png";
        static constexpr std::string_view ASSAULT_RIFLE_01_SHOP = "assets/Graphics/Weapons/Guns/assault_rifle_01_shop.png";
    };

    struct Fonts
    {
        static constexpr std::string_view LIBERATION_SANS = "assets/Fonts/LiberationSans.ttf";
        static constexpr std::string_view PIXEL_OPERATOR_8 = "assets/Fonts/PixelOperator8.ttf";
        static constexpr std::string_view PIXEL_OPERATOR_8_BOLD = "assets/Fonts/PixelOperator8-Bold.ttf";
        static constexpr std::string_view ANTON = "assets/Fonts/Anton.ttf";
        static constexpr std::string_view BANGERS = "assets/Fonts/Bangers.ttf";
        static constexpr std::string_view OSWALD_BOLD = "assets/Fonts/Oswald-Bold.ttf";
        static constexpr std::string_view ROBOTO_BOLD = "assets/Fonts/Roboto-Bold.ttf";
    };

};

#endif // ASSET_H
