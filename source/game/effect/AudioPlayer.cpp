#include "game/effect/AudioPlayer.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"

void AudioPlayer::init(const string& ref, const float& volume, bool autoDestroy)
{
    auto buffer = SoundBase::get(ref);

    if (buffer)
    {
        m_sound.setBuffer(*buffer);
    }
    else
    {
        VDebuger::print("<ERROR> AUDIO_PLAYER :: buffer is nullptr");
        return;
    }

    m_sound.setVolume(volume);

    m_isInited = true;
    m_autoDestroy = autoDestroy;
}


void AudioPlayer::play()
{
    m_isInvoked = true;

    if (!isPlaying())
    {
        m_sound.play();
    }
}


void AudioPlayer::onUpdate(float)
{
    if (m_autoDestroy && m_isInvoked && !isPlaying())
    {
        if (getGame() && getGame()->get_currentScene()) {
            getGame()->get_currentScene()->killObject(this, true);
        }
    }
}


bool AudioPlayer::isPlaying()
{
    return m_sound.getStatus() == sf::SoundSource::Playing;
}
