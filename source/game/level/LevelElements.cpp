#include "game/level/LevelElements.h"
#include "engine/component/Collider.h"
#include "engine/core/Engine.h"
#include "game/core/DataBlock.h"
#include "game/core/Tag.h"
#include "game/effect/CustomAnimation.h"
#include "game/effect/ParticleEffect.h"
#include "game/level/LevelManager.h"


///
/// Chest
///

shared_ptr<sf::Texture> Chest::particleTexture = nullptr;

void Chest::onAwake()
{
    //tag
    this->addTag("chest");

    //parts
    body = getGame()->get_currentScene()->createObject<GameObject>(getRenderLayer());
    body->getTransformPtr()->scaleBy(2.f);
    this->addChild(body);

    //collider
    collider = createComponent<CircleCollider>();
    collider->set(50.f);

    //animations
    animContr = createComponent<AnimationController>();


    //notification manager
    notificationManager = getGame()->get_currentScene()->findObject<NotificationManager>();

    if (!notificationManager) {
        VDebuger::print("<ERROR> CHEST :: ON_AWAKE :: notificationManager is nullptr");
    }


    //particle effects
    parEff = getGame()->get_currentScene()->createObject<ParticleEffect>(body->getRenderLayer()+1u);
    parEff->addTag("particle_effect_chest");
    this->addChild(parEff);

    if (!particleTexture)
    {
        particleTexture = make_shared<sf::Texture>();

        if (!particleTexture->loadFromFile(Asset::Graphics::PARTICLE.data())) {
            VDebuger::print("<ERROR> CHEST :: ON_AWAKE :: cant load particle texture");
        }
    }

    parEff->setTexture(particleTexture);

    parEff->setColor(sf::Color::Yellow);
    parEff->setScale(Vector2(0.15f, 0.15f));

    parEff->setSpread(60.0f);

    parEff->setSpeed(5.0f);
    parEff->setSpeedDiff(5.f);

    parEff->setLifeTime(300.0f);
    parEff->setLifeTimeDiff(200.0f);

    parEff->setParticleNumDiff(0u);
}

void Chest::onUpdate(float)
{
    if (m_isOpened)
    {
        if (!m_isLooted &&
            animContr->getCurrentAnimation() < 0) {
            this->empty();
        }

        return;
    }


    if (!collider) {
        VDebuger::print("<ERROR> CHEST :: collider is nullptr");
        return;
    }


    for (const auto& coll : collider->getCollisions())
    {
        if (!coll) {
            continue;
        }

        auto obj = coll->getObject();

        if (!obj) {
            continue;
        }

        //only for player
        if (obj->checkTag(Tag::PLAYER_CORE.data()))
        {
            this->open();
        }
    }
}

void Chest::open()
{
    if (m_isOpened) {
        return;
    }

    m_isOpened = true;
    animContr->play(ANIM_OPEN);
}

void Chest::empty()
{
    if (m_isLooted) {
        return;
    }

    m_isLooted = true;
    PlayerData::setCoins(PlayerData::getCoins() + this->coins);

    //notifacation
    if (notificationManager)
    {
        std::ostringstream oss;
        oss << "+" << this->coins << " coins";
        notificationManager->message(oss.str());
    }

    this->coins = 0u;
    animContr->play(ANIM_EMPTY);

    if (parEff)
    {
        parEff->invoke(Vector2(0.f, 1.f), false);
    }
    else
    {
        VDebuger::print("<ERROR> CHEST :: player is nullptr");
    }

}

void Chest::set(const string_view txt_close_ref,
                const string_view txt_open_full_ref,
                const string_view txt_open_empty_ref)
{
    //body
    if (!body) {
        VDebuger::print("<ERROR> CHEST :: SET :: body is nullptr");
        return;
    }


    //main
    body->getSpritePtr()->setTexture(txt_close_ref.data());

    //other
    shared_ptr<sf::Texture> txt_open_full = make_shared<sf::Texture>();
    shared_ptr<sf::Texture> txt_open_empty = make_shared<sf::Texture>();

    if (!txt_open_full->loadFromFile(txt_open_full_ref.data()) ||
        !txt_open_empty->loadFromFile(txt_open_empty_ref.data()))
    {
        VDebuger::print("<ERROR> CHEST :: load texture error");
    }


    //animations
    {
        //open
        {
            //params
            const float d_move = 0.1f;
            const float d_move_n = 10.f;

            //texture change

            auto am_open_txt1 = make_shared<AnimationTextureMove>(body->getSpritePtr(),
                                                                  txt_open_full,
                                                                  body->getSpritePtr()->getTextureRect(),
                                                                  d_move * d_move_n);

            AnimationCycle cyckle_open_txt({am_open_txt1});


            //vibrations

            auto am_open_move1 = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                                     body->getTransformPtr()->get_localPosition() - Vector2(2.f),
                                                                     body->getTransformPtr()->get_localPosition() + Vector2(2.f),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     d_move);

            auto am_open_move2 = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                                     body->getTransformPtr()->get_localPosition() + Vector2(2.f),
                                                                     body->getTransformPtr()->get_localPosition() - Vector2(2.f),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     d_move);

            vector<shared_ptr<AnimationStep>> am_open_move;
            for (int i = 0; i < 2; ++i)
            {
                am_open_move.emplace_back(am_open_move1);
                am_open_move.emplace_back(am_open_move2);
            }

            AnimationCycle cyckle_open_move(am_open_move);


            //animation

            Animation anim_open({cyckle_open_txt, cyckle_open_move});
            ANIM_OPEN = animContr->add(anim_open);
        }

        //empty
        {
            auto am_open_txt = make_shared<AnimationTextureMove>(body->getSpritePtr(),
                                                                 txt_open_empty,
                                                                 body->getSpritePtr()->getTextureRect(),
                                                                 0.1f);

            auto am_open_move = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                                    body->getTransformPtr()->get_localPosition(),
                                                                    body->getTransformPtr()->get_localPosition(),
                                                                    body->getTransformPtr()->get_scale(),
                                                                    body->getTransformPtr()->get_scale(),
                                                                    body->getTransformPtr()->get_rotation(),
                                                                    body->getTransformPtr()->get_rotation(),
                                                                    0.1f);

            AnimationCycle cyckle_open_move({am_open_txt, am_open_move});

            Animation anim_open_empty({cyckle_open_move});
            ANIM_EMPTY = animContr->add(anim_open_empty);
        }
    }
}

void Chest::addCoins(const uint& coins) {
    this->coins += coins;
    parEff->setParticleNum(this->coins);
}


///
/// \brief FinishPoint
///

void FinishPoint::onAwake()
{
    if (!getGame() || !getGame()->get_currentScene()) {
        VDebuger::print("<ERROR> FINISH_POINTER :: ON_AWAKE :: game or scene is nullptr");
    }


    //level manager

    levelManager = getGame()->get_currentScene()->findObject<LevelManager>();

    if (!levelManager) {
        VDebuger::print("<ERROR> FINISH_POINTER :: ON_AWAKE :: levelManager is nullptr");
    }


    //collider

    collider = createComponent<CircleCollider>();

    if (collider)
    {
        collider->set(50.f);
    }
    else
    {
        VDebuger::print("<ERROR> FINISH_POINTER :: ON_AWAKE :: collider is nullptr");
    }


    //texture

    getSpritePtr()->setTexture(Asset::Graphics::FLOOR_LADDER.data());


    //scale

    getTransformPtr()->scaleBy(2.f);
}

void FinishPoint::onUpdate(float dt)
{
    if (!collider) {
        return;
    }


    for (const auto& coll : collider->getCollisions())
    {
        if (!coll) {
            continue;
        }

        auto obj = coll->getObject();

        if (!obj) {
            continue;
        }

        //only for player
        if (obj->checkTag(Tag::PLAYER_CORE.data()))
        {
            //finish
            //levelManager->finishLevel();
        }
    }
}
