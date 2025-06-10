#include "game/player/PlayerHealthSystem.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"

void PlayerHealthSystem::onAwake()
{
    if (!getGame() || !getGame()->get_currentScene())
    {
        return;
    }

    setHealthBar(getGame()->get_currentScene()->findObject<Slider>(Tag::PLAYER_HEALTH_BAR.data()));
}
