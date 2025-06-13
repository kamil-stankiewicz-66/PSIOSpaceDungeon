#ifndef ASSET_H
#define ASSET_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Audio/SoundBuffer.hpp>
#include <map>
#include <memory>
#include <string_view>

using namespace std;


///
/// \brief The Asset struct.
///

struct Asset
{
    static constexpr string_view INIT_FILE = "assets/parameters_init.txt";

    struct Graphics
    {
        //chests
        static constexpr string_view CHEST_CLOSED = "assets/Graphics/Chest/chest_closed.png";
        static constexpr string_view CHEST_GOLDEN_CLOSED = "assets/Graphics/Chest/chest_golden_closed.png";
        static constexpr string_view CHEST_GOLDEN_OPEN_EMPTY = "assets/Graphics/Chest/chest_golden_open_empty.png";
        static constexpr string_view CHEST_GOLDEN_OPEN_FULL = "assets/Graphics/Chest/chest_golden_open_full.png";
        static constexpr string_view CHEST_OPEN_EMPTY = "assets/Graphics/Chest/chest_open_empty.png";
        static constexpr string_view CHEST_OPEN_FULL = "assets/Graphics/Chest/chest_open_full.png";

        //zombies
        static constexpr string_view ZOMBIE_BASIC = "assets/Graphics/Entities/monster_zombie.png";
        static constexpr string_view ZOMBIE_GREEN = "assets/Graphics/Entities/monster_zombie_green.png";
        static constexpr string_view ZOMBIE_SHORT = "assets/Graphics/Entities/monster_zombie_short.png";
        static constexpr string_view ZOMBIE_SMALL = "assets/Graphics/Entities/monster_zombie_small.png";
        static constexpr string_view ZOMBIE_TALL = "assets/Graphics/Entities/monster_zombie_tall.png";
        static constexpr string_view ZOMBIE_SKELET = "assets/Graphics/Entities/monster_skelet.png";

        //orcs
        static constexpr string_view ORC_BASIC = "assets/Graphics/Entities/monster_orc.png";
        static constexpr string_view ORC_ARMORED = "assets/Graphics/Entities/monster_orc_armored.png";
        static constexpr string_view ORC_MASKED = "assets/Graphics/Entities/monster_orc_masked.png";
        static constexpr string_view ORC_SHAMAN = "assets/Graphics/Entities/monster_orc_shaman.png";
        static constexpr string_view ORC_VETERAN = "assets/Graphics/Entities/monster_orc_veteran.png";

        //elementals
        static constexpr string_view ELEMENTAL_AIR = "assets/Graphics/Entities/monster_elemental_air.png";
        static constexpr string_view ELEMENTAL_GOLD_SHORT = "assets/Graphics/Entities/monster_elemental_gold_short.png";
        static constexpr string_view ELEMENTAL_GOLD_TALL = "assets/Graphics/Entities/monster_elemental_gold_tall.png";
        static constexpr string_view ELEMENTAL_GOO = "assets/Graphics/Entities/monster_elemental_goo.png";
        static constexpr string_view ELEMENTAL_GOO_SMALL = "assets/Graphics/Entities/monster_elemental_goo_small.png";
        static constexpr string_view ELEMENTAL_PLANT = "assets/Graphics/Entities/monster_elemental_plant.png";
        static constexpr string_view ELEMENTAL_PLANT_SMALL = "assets/Graphics/Entities/monster_elemental_plant_small.png";

        //monsters
        static constexpr string_view MONSTER_BIES = "assets/Graphics/Entities/monster_bies.png";
        static constexpr string_view MONSTER_CHORT = "assets/Graphics/Entities/monster_chort.png";
        static constexpr string_view MONSTER_DARK_KNIGHT = "assets/Graphics/Entities/monster_dark_knight.png";
        static constexpr string_view MONSTER_DEMONOLOG = "assets/Graphics/Entities/monster_demonolog.png";
        static constexpr string_view MONSTER_ROKITA = "assets/Graphics/Entities/monster_rokita.png";
        static constexpr string_view MONSTER_WOGOLO = "assets/Graphics/Entities/monster_wogol.png";
        static constexpr string_view MONSTER_NECROMANCER = "assets/Graphics/Entities/monster_necromancer.png";
        static constexpr string_view MONSTER_IMP = "assets/Graphics/Entities/monster_imp.png";
        static constexpr string_view MONSTER_GOBLIN = "assets/Graphics/Entities/monster_goblin.png";
        static constexpr string_view MONSTER_OGRE = "assets/Graphics/Entities/monster_ogre.png";

        //GUI
        static constexpr string_view LEFTRIGHT_ARROWS = "assets/Graphics/GUI/leftRightArrows.png";
        static constexpr string_view BUTTON = "assets/Graphics/GUI/button.png";
        static constexpr string_view PANEL = "assets/Graphics/GUI/panel.png";
        static constexpr string_view HEALTHBAR = "assets/Graphics/GUI/HealthBar.png";

        //particles
        static constexpr string_view PARTICLE = "assets/Graphics/Particles/particle.png";

        //player
        static constexpr string_view CAPE_BASE = "assets/Graphics/Player/cape_base.png";
        static constexpr string_view PLAYER_SKIN_01 = "assets/Graphics/Player/player_skin_01.png";
        static constexpr string_view PLAYER_SKIN_02 = "assets/Graphics/Player/player_skin_02.png";

        //tilesets
        static constexpr string_view BOXES = "assets/Graphics/Tilesets/boxes.png";
        static constexpr string_view COLUMNS = "assets/Graphics/Tilesets/columns.png";
        static constexpr string_view DOOR = "assets/Graphics/Tilesets/door.png";
        static constexpr string_view EMPTY = "assets/Graphics/Tilesets/empty.png";
        static constexpr string_view FLOOR_LADDER = "assets/Graphics/Tilesets/floor_ladder.png";
        static constexpr string_view FLOOR_LIGHT = "assets/Graphics/Tilesets/floor_light.png";
        static constexpr string_view FLOOR_MAIN = "assets/Graphics/Tilesets/floor_main.png";
        static constexpr string_view FLOOR_PLATES = "assets/Graphics/Tilesets/floor_plates.png";
        static constexpr string_view GARGOYLES = "assets/Graphics/Tilesets/gargoyles.png";
        static constexpr string_view HOLE = "assets/Graphics/Tilesets/hole.png";
        static constexpr string_view SKULL_01 = "assets/Graphics/Tilesets/skull_01.png";
        static constexpr string_view STAIRS = "assets/Graphics/Tilesets/stairs.png";
        static constexpr string_view WALL_BROKEN = "assets/Graphics/Tilesets/wall_broken.png";
        static constexpr string_view WALL_CLOSED = "assets/Graphics/Tilesets/wall_closed.png";
        static constexpr string_view WALL_CRATES = "assets/Graphics/Tilesets/wall_crates.png";
        static constexpr string_view WALL_FLAGS = "assets/Graphics/Tilesets/wall_flags.png";
        static constexpr string_view WALL_MAIN = "assets/Graphics/Tilesets/wall_main.png";
        static constexpr string_view WALL_PIPES = "assets/Graphics/Tilesets/wall_pipes.png";
        static constexpr string_view WALL_SLIME = "assets/Graphics/Tilesets/wall_slime.png";

        //weapons
        static constexpr string_view LASER_BULLET = "assets/Graphics/Weapons/laser_bullet.png";
        static constexpr string_view MASHINE_PISTOL_01 = "assets/Graphics/Weapons/Guns/machine_pistol_01.png";
        static constexpr string_view ASSAULT_RIFLE_01 = "assets/Graphics/Weapons/Guns/assault_rifle_01.png";
        static constexpr string_view SHOTGUN_01 = "assets/Graphics/Weapons/Guns/shotgun_01.png";
        static constexpr string_view ASSAULT_RIFLE_01_SHOP = "assets/Graphics/Weapons/Guns/assault_rifle_01_shop.png";
        static constexpr string_view PISTOL = "assets/Graphics/weapons/Guns/pistol_01.png";
    };

    struct Fonts
    {
        static constexpr string_view LIBERATION_SANS = "assets/Fonts/LiberationSans.ttf";
        static constexpr string_view PIXEL_OPERATOR_8 = "assets/Fonts/PixelOperator8.ttf";
        static constexpr string_view PIXEL_OPERATOR_8_BOLD = "assets/Fonts/PixelOperator8-Bold.ttf";
        static constexpr string_view ANTON = "assets/Fonts/Anton.ttf";
        static constexpr string_view BANGERS = "assets/Fonts/Bangers.ttf";
        static constexpr string_view OSWALD_BOLD = "assets/Fonts/Oswald-Bold.ttf";
        static constexpr string_view ROBOTO_BOLD = "assets/Fonts/Roboto-Bold.ttf";
    };

    struct Audio
    {
        //effect
        static constexpr string_view END_LEVEL = "assets/Audio/Effect/end-level.ogg";

        //entity
        static constexpr string_view BITE = "assets/Audio/Entity/bite.ogg";
        static constexpr string_view GUN = "assets/Audio/Entity/gun.ogg";
        static constexpr string_view GUN_MACHINE = "assets/Audio/Entity/gun_machine.ogg";
        static constexpr string_view GUN_SHOTGUN = "assets/Audio/Entity/gun_shotgun.ogg";
        static constexpr string_view HIT_FINISHER_73 = "assets/Audio/Entity/hit_finisher_73.wav";
        static constexpr string_view HIT_FINISHER_61 = "assets/Audio/Entity/hit_finisher_61.wav";
        static constexpr string_view HIT_FINISHER_52 = "assets/Audio/Entity/hit_finisher_52.wav";
        static constexpr string_view HIT_FINISHER_40 = "assets/Audio/Entity/hit_finisher_40.wav";
        static constexpr string_view HIT_FINISHER_23 = "assets/Audio/Entity/hit_finisher_23.wav";
        static constexpr string_view HIT_FINISHER_19 = "assets/Audio/Entity/hit_finisher_19.wav";

        //music
        static constexpr string_view GOBLINS_DANCE_BATTLE = "assets/Audio/Music/Goblins_Dance_(Battle).wav";
        static constexpr string_view FROM_THE_DARK_PAST = "assets/Audio/Music/From_the_Dark_Past.ogg";

        //player
        static constexpr string_view PLAYER_DAMAGE_GRUNT_01 = "assets/Audio/Player/01_Damage_Grunt.wav";
        static constexpr string_view PLAYER_DAMAGE_GRUNT_02 = "assets/Audio/Player/02_Damage_Grunt.wav";
        static constexpr string_view PLAYER_DAMAGE_GRUNT_03 = "assets/Audio/Player/03_Damage_Grunt.wav";
        static constexpr string_view PLAYER_DAMAGE_GRUNT_05 = "assets/Audio/Player/05_Damage_Grunt.ogg";
        static constexpr string_view PLAYER_DAMAGE_GRUNT_06 = "assets/Audio/Player/06_Damage_Grunt.ogg";
    };
};


///
/// \brief Preloaded textures base.
///

class TextureBase
{
    //static texture base [path, texture]
    static map<string, unique_ptr<sf::Texture>> textures;

public:

    //get texture
    static sf::Texture* get(const string& assetPath);
};


///
/// \brief Preloaded fontes base.
///

class FontBase
{
    // static font base [path, font]
    static map<string, unique_ptr<sf::Font>> fonts;

public:

    // get font
    static sf::Font* get(const string& assetPath);
};


///
/// \brief Preloaded sound buffers base.
///

class SoundBase
{
    //static sound buffer base [path, sound buffer]
    static map<string, unique_ptr<sf::SoundBuffer>> soundBuffers;

public:

    //get sound buffer
    static sf::SoundBuffer* get(const string& assetPath);
};

#endif // ASSET_H
