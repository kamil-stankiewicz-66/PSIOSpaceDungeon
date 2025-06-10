#include "game/player/PlayerHealthSystem.h"
#include "engine/core/Engine.h"
#include "engine/core/Input.h"
#include "game/core/Parameter.h"
#include "game/core/Tag.h"
#include "game/level/LevelManager.h"

void PlayerHealthSystem::onAwake()
{
    if (!getGame() || !getGame()->get_currentScene())
    {
        return;
    }

    setHealthBar(getGame()->get_currentScene()->findObject<Slider>(Tag::PLAYER_HEALTH_BAR.data()));
    setHealBar(getGame()->get_currentScene()->findObject<Slider>(Tag::PLAYER_HEAL_BAR.data()));

    levelManager = getGame()->get_currentScene()->findObject<LevelManager>();
}

void PlayerHealthSystem::onUpdate(float dt)
{
    //regeneration with heal points
    if (Input::Keyboard::isKeyPressed(Input::Keyboard::Key::R) &&
        healPoints > 0.0f &&
        getHealth() < getHealthMax())
    {
        m_isHealing = true;

        float value = dt * 10.0f * Parameters::get_player_regenerationRate();
        subHealPoints(value);
        addHealth(value);
    }
    else
    {
        m_isHealing = false;
    }

    //auto regeneration
    addHealth(dt * Parameters::get_player_regenerationRate());
}


void PlayerHealthSystem::setHealBar(Slider* slider)
{
    healBar = slider;
    refreshHealBar();
}


void PlayerHealthSystem::setHealPoints(const float& v)
{
    this->healPoints = v;

    if (healPoints > healPointsMax) {
        this->healPointsMax = healPoints;
    }

    refreshHealBar();
}


void PlayerHealthSystem::refreshHealBar()
{
    if (healBar && (healPointsMax > 0.0f))
    {
        healBar->setValueMax(healPointsMax);
        healBar->setValue(healPoints);
    }
}


void PlayerHealthSystem::addHealPoints(const float& v)
{
    healPoints += v;

    if (healPoints > healPointsMax) {
        healPoints = healPointsMax;
    }

    refreshHealBar();
}

void PlayerHealthSystem::subHealPoints(const float& v)
{
    healPoints -= v;

    if (healPoints < 0.0f) {
        healPoints = 0.0f;
    }

    refreshHealBar();
}


const float& PlayerHealthSystem::getHealPoints() const {
    return healPoints;
}

const float& PlayerHealthSystem::getHealPointsMax() const {
    return healPointsMax;
}
