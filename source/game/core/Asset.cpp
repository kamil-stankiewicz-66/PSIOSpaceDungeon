#include "game/core/Asset.h"
#include "engine/core/Debuger.h"

std::map<std::string, std::shared_ptr<sf::Texture>> TextureBase::textures;

std::shared_ptr<sf::Texture> TextureBase::get(std::string assetPath)
{
    auto it = textures.find(assetPath.data());

    if (it != textures.end())
    {
        return it->second;
    }

    auto tex = std::make_shared<sf::Texture>();
    if (tex->loadFromFile(assetPath))
    {
        textures.emplace(assetPath, tex);

        //log
        VDebuger::print("TEXTURE_BASE :: texture loading successful:", assetPath.data());

        return tex;
    }

    //log
    VDebuger::print("<ERROR> TEXTURE_BASE :: texture loading error:", assetPath.data());

    return nullptr;
}

void TextureBase::preloadAll()
{
    // chest
    get(Asset::Graphics::CHEST_CLOSED.data());
    get(Asset::Graphics::CHEST_GOLDEN_CLOSED.data());
    get(Asset::Graphics::CHEST_GOLDEN_OPEN_EMPTY.data());
    get(Asset::Graphics::CHEST_GOLDEN_OPEN_FULL.data());
    get(Asset::Graphics::CHEST_OPEN_EMPTY.data());
    get(Asset::Graphics::CHEST_OPEN_FULL.data());

    // entities
    get(Asset::Graphics::HEALTHBAR.data());

    // orcs
    get(Asset::Graphics::ORC_ARMORED.data());
    get(Asset::Graphics::ORC_BASIC.data());
    get(Asset::Graphics::ORC_MASKED.data());
    get(Asset::Graphics::ORC_SHAMAN.data());
    get(Asset::Graphics::ORC_VETERAN.data());

    // zombies
    get(Asset::Graphics::ZOMBIE_SKELETON.data());
    get(Asset::Graphics::ZOMBIE_BASIC.data());
    get(Asset::Graphics::ZOMBIE_GREEN.data());
    get(Asset::Graphics::ZOMBIE_SHORT.data());
    get(Asset::Graphics::ZOMBIE_SMALL.data());
    get(Asset::Graphics::ZOMBIE_TALL.data());

    // GUI
    get(Asset::Graphics::LEFTRIGHT_ARROWS.data());
    get(Asset::Graphics::BUTTON.data());
    get(Asset::Graphics::PANEL.data());

    // particle
    get(Asset::Graphics::PARTICLE.data());

    // player
    get(Asset::Graphics::CAPE_BASE.data());
    get(Asset::Graphics::PLAYER_SKIN_01.data());
    get(Asset::Graphics::PLAYER_SKIN_02.data());

    // tilesets
    get(Asset::Graphics::BOXES.data());
    get(Asset::Graphics::COLUMNS.data());
    get(Asset::Graphics::DOOR.data());
    get(Asset::Graphics::EMPTY.data());
    get(Asset::Graphics::FLOOR_LADDER.data());
    get(Asset::Graphics::FLOOR_LIGHT.data());
    get(Asset::Graphics::FLOOR_MAIN.data());
    get(Asset::Graphics::FLOOR_PLATES.data());
    get(Asset::Graphics::GARGOYLES.data());
    get(Asset::Graphics::HOLE.data());
    get(Asset::Graphics::SKULL_01.data());
    get(Asset::Graphics::STAIRS.data());
    get(Asset::Graphics::WALL_BROKEN.data());
    get(Asset::Graphics::WALL_CLOSED.data());
    get(Asset::Graphics::WALL_CRATES.data());
    get(Asset::Graphics::WALL_FLAGS.data());
    get(Asset::Graphics::WALL_MAIN.data());
    get(Asset::Graphics::WALL_PIPES.data());
    get(Asset::Graphics::WALL_SLIME.data());

    // weapons
    get(Asset::Graphics::LASER_BULLET.data());
    get(Asset::Graphics::MASHINE_PISTOL_01.data());
    get(Asset::Graphics::ASSAULT_RIFLE_01.data());
    get(Asset::Graphics::SHOTGUN_01.data());
    get(Asset::Graphics::ASSAULT_RIFLE_01_SHOP.data());
}
