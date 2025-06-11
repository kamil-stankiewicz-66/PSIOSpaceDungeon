#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "SFML/Audio/Sound.hpp"
#include "engine/object/Object.h"

class AudioPlayer : public Object
{
    sf::Sound m_sound;
    bool m_isInited;
    bool m_autoDestroy;
    bool m_isInvoked;

public:

    ///
    /// \brief Init audio player
    /// \param sound_ref path to sound file
    /// \param volume from 0.0f to 100.0f
    /// \param autoDestroy destroy after play?
    ///

    void init(const string& sound_ref, const float& volume = 100.0f, bool autoDestroy = false);

    ///
    /// \brief Play sound (and destroy if autoDestroy = true)
    ///

    void play();

private:

    //engine
    virtual void onUpdate(float) override;

    //helper
    bool isPlaying();
};

#endif // AUDIOPLAYER_H
