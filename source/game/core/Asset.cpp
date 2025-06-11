#include "game/core/Asset.h"
#include "engine/core/Debuger.h"



///
/// TextureBase
///


std::map<std::string, std::unique_ptr<sf::Texture>> TextureBase::textures;

sf::Texture* TextureBase::get(const std::string& assetPath)
{
    auto it = textures.find(assetPath);
    if (it != textures.end())
    {
        return it->second.get();
    }

    auto tex = std::make_unique<sf::Texture>();
    if (tex->loadFromFile(assetPath))
    {
        sf::Texture* texPtr = tex.get();
        textures.emplace(assetPath, std::move(tex));

        // log
        VDebuger::print("TEXTURE_BASE :: texture loading successful:", assetPath.c_str());

        return texPtr;
    }

    // log
    VDebuger::print("<ERROR> TEXTURE_BASE :: texture loading error:", assetPath.c_str());

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




///
/// SoundBase
///

std::map<std::string, std::unique_ptr<sf::SoundBuffer>> SoundBase::soundBuffers;

sf::SoundBuffer* SoundBase::get(const std::string& assetPath)
{
    auto it = soundBuffers.find(assetPath);
    if (it != soundBuffers.end())
    {
        return it->second.get();
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (buffer->loadFromFile(assetPath))
    {
        sf::SoundBuffer* bufPtr = buffer.get();
        soundBuffers[assetPath] = std::move(buffer);

        // log
        VDebuger::print("AUDIO_BASE :: audio loading successful:", assetPath.c_str());
        return bufPtr;
    }

    // log
    VDebuger::print("<ERROR> AUDIO_BASE :: audio loading error:", assetPath.c_str());

    return nullptr;
}

void SoundBase::preloadAll()
{
    get(Asset::Audio::END_LEVEL.data());
    get(Asset::Audio::BITE.data());
    get(Asset::Audio::GUN.data());
    get(Asset::Audio::SCREAM.data());
    get(Asset::Audio::GOBLINS_DANCE_BATTLE.data());
    get(Asset::Audio::PLAYER_DAMAGE_GRUNT_01.data());
    get(Asset::Audio::PLAYER_DAMAGE_GRUNT_02.data());
    get(Asset::Audio::PLAYER_DAMAGE_GRUNT_03.data());
    get(Asset::Audio::PLAYER_DAMAGE_GRUNT_05.data());
    get(Asset::Audio::PLAYER_DAMAGE_GRUNT_06.data());
}
