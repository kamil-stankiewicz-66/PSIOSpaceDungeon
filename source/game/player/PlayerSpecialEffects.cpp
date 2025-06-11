#include "game/player/PlayerSpecialEffects.h"
#include "engine/core/Engine.h"
#include "game/player/PlayerCore.h"

void PlayerSpecialEffects::onAwake()
{
    playerCore = dynamic_cast<PlayerCore*>(getObject());

    if (!playerCore)
    {
        VDebuger::print("<ERROR> PLAYER_SPECIAL_EFFECTS :: player core is nullptr");
        return;
    }


    //particle effect

    parEff = getGame()->get_currentScene()->createObject<ParticleEffect>(playerCore->getRenderLayer() -1u);
    parEff->addTag("particle_effect");

    parEff->setTexture(Asset::Graphics::PARTICLE);

    parEff->setColor(sf::Color::Yellow);
    parEff->setScale(Vector2(0.07f, 0.07f));

    parEff->setSpread(180.0f);

    parEff->setSpeed(5.0f);
    parEff->setSpeedDiff(3.5f);

    parEff->setLifeTime(150.0f);
    parEff->setLifeTimeDiff(30.0f);

    parEff->setParticleNum(1u);
    parEff->setParticleNumDiff(0u);
}


void PlayerSpecialEffects::onUpdate(float dt)
{
    if (!playerCore) {
        return;
    }

    //particle effect
    if (playerCore->healthSystem->isHealing())
    {
        parEff->getTransformPtr()->set_position(playerCore->playerRect->getTransformPtr()->get_position());
        parEff->invoke(Vector2(0.0f, 1.0f), false);
    }
}
