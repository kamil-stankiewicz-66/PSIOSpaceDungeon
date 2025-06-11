#include "game/core/Asset.h"
#include "engine/core/Debuger.h"




///
/// TextureBase
///


map<string, unique_ptr<sf::Texture>> TextureBase::textures;

sf::Texture* TextureBase::get(const string& assetPath)
{
    auto it = textures.find(assetPath);
    if (it != textures.end())
    {
        return it->second.get();
    }

    auto tex = make_unique<sf::Texture>();
    if (tex->loadFromFile(assetPath))
    {
        sf::Texture* texPtr = tex.get();
        textures.emplace(assetPath, std::move(tex));

        //log
        VDebuger::print("TEXTURE_BASE :: texture loading successful:", assetPath.c_str());

        return texPtr;
    }

    //log
    VDebuger::print("<ERROR> TEXTURE_BASE :: texture loading error:", assetPath.c_str());

    return nullptr;
}




///
/// FontBase
///


map<string, unique_ptr<sf::Font>> FontBase::fonts;

sf::Font* FontBase::get(const string& assetPath)
{
    auto it = fonts.find(assetPath);
    if (it != fonts.end())
    {
        return it->second.get();
    }

    auto font = make_unique<sf::Font>();
    if (font->loadFromFile(assetPath))
    {
        sf::Font* fontPtr = font.get();
        fonts.emplace(assetPath, std::move(font));

        //log
        VDebuger::print("FONT_BASE :: font loading successful:", assetPath.c_str());

        return fontPtr;
    }

    //log
    VDebuger::print("<ERROR> FONT_BASE :: font loading error:", assetPath.c_str());

    return nullptr;
}




///
/// SoundBase
///

map<string, unique_ptr<sf::SoundBuffer>> SoundBase::soundBuffers;

sf::SoundBuffer* SoundBase::get(const string& assetPath)
{
    auto it = soundBuffers.find(assetPath);
    if (it != soundBuffers.end())
    {
        return it->second.get();
    }

    auto buffer = make_unique<sf::SoundBuffer>();
    if (buffer->loadFromFile(assetPath))
    {
        sf::SoundBuffer* bufPtr = buffer.get();
        soundBuffers[assetPath] = std::move(buffer);

        //log
        VDebuger::print("AUDIO_BASE :: audio loading successful:", assetPath.c_str());
        return bufPtr;
    }

    //log
    VDebuger::print("<ERROR> AUDIO_BASE :: audio loading error:", assetPath.c_str());

    return nullptr;
}
