#include "game/level/LevelElements.h"
#include "engine/component/Collider.h"
#include "engine/core/Engine.h"
#include "game/core/DataBlock.h"
#include "game/core/Tag.h"
#include "game/effect/CustomAnimation.h"


///
/// AbstractChest
///

void Chest::onAwake()
{
    //parts
    body = getGame()->get_currentScene()->createObject<GameObject>(getRenderLayer());
    body->getTransformPtr()->scaleBy(2.f);
    this->addChild(body);

    //collider
    collider = createComponent<CircleCollider>();
    collider->set(50.f);

    //animations
    animContr = createComponent<AnimationController>();
}

void Chest::onUpdate(float)
{
    if (m_isOpened)
    {
        if (animContr->getCurrentAnimation() < 0) {
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
    PlayerData::coins += this->coins;
    this->coins = 0u;
    animContr->play(ANIM_EMPTY);
}

void Chest::set(const string_view txt_close_ref,
                const string_view txt_open_full_ref,
                const string_view txt_open_empty_ref)
{
    //body
    if (!body) {
        VDebuger::print("<ERROR> CHEST :: SET :: body is nullptr");
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

            auto am_open_move1 = make_shared<AnimationTransformMove>(body->getTransformPtr(),
                                                                     body->getTransformPtr()->get_position() - Vector2(2.f),
                                                                     body->getTransformPtr()->get_position() + Vector2(2.f),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     d_move);

            auto am_open_move2 = make_shared<AnimationTransformMove>(body->getTransformPtr(),
                                                                     body->getTransformPtr()->get_position() + Vector2(2.f),
                                                                     body->getTransformPtr()->get_position() - Vector2(2.f),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_scale(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     body->getTransformPtr()->get_rotation(),
                                                                     d_move);

            vector<shared_ptr<AnimationMove>> am_open_move;
            for (int i = 0; i < (d_move_n/2.f); ++i)
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

            auto am_open_move = make_shared<AnimationTransformMove>(body->getTransformPtr(),
                                                                    body->getTransformPtr()->get_position(),
                                                                    body->getTransformPtr()->get_position(),
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
