#include "game/entity/Entity.h"
#include "engine/core/Engine.h"
#include "game/core/Parameter.h"
#include "game/core/Tag.h"
#include "game/physics/Rycast.h"
#include "game/core/Asset.h"
#include "game/player/PlayerCore.h"

Entity::Entity() : rng(std::random_device{}())
{}


///
/// engine
///

void Entity::onAwake()
{
    //state
    state = EntityState::Sleep;

    //tag
    this->addTag(Tag::ENEMY.data());


    if (!getGame() || !getGame()->get_currentScene())
    {
        VDebuger::print("<ERROR> ENTITY :: ON_AWAKE :: game or scene is nullptr");
        return;
    }



    //parts
    body = getGame()->get_currentScene()->createObject<GameObject>(getRenderLayer());
    this->addChild(body);
    hand = getGame()->get_currentScene()->createObject<GameObject>(getRenderLayer());
    body->addChild(hand);

    //health bar
    healthBar = getGame()->get_currentScene()->createObject<Slider>(getRenderLayer()+1u);
    this->addChild(healthBar);
    healthBar->init(false);
    healthBar->setFillColor(sf::Color::Red);
    healthBar->setBackgroundColor(sf::Color(23, 26, 33));
    healthBar->scaleWidth(0.2);
    healthBar->scaleHeight(0.25f);



    //componets
    collider = createComponent<BoxCollider>();;

    rb = createComponent<Rigidbody>();
    rb->init(getTransformPtr(), getTransformPtr());

    animController = createComponent<AnimationController>();

    healthSystem = createComponent<EntityHealthSystem>();


    //find objects

    if (GameObject* playerRect = getGame()->get_currentScene()->findGameObject(Tag::PLAYER_RECT.data()))
    {
        player = playerRect->getTransformPtr();
        tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());
    }

    if (!player || !tilemap) {
        VDebuger::print("<ERROR> :: ENTITY :: player or tilemap is nullptr");
    }



    if (!player->getObject()) {
        VDebuger::print("<ERROR> ENTITY :: ON_AWAKE :: player object is nullptr");
        return;
    }


    //particle effect

    particleEfect = getGame()->get_currentScene()->createObject<ParticleEffect>(25u);

    if (!particleTexture)
    {
        particleTexture = make_shared<sf::Texture>();

        if (!particleTexture->loadFromFile(Asset::Graphics::PARTICLE.data())) {
            VDebuger::print("<ERROR> ENTITY :: INIT :: cant load particle texture");
        }
    }

    particleEfect->setTexture(particleTexture);

    particleEfect->setColor(sf::Color::Red);
    particleEfect->setScale(Vector2(0.2f, 0.2f));

    particleEfect->setSpread(360.0f);

    particleEfect->setSpeed(0.2f);
    particleEfect->setSpeedDiff(0.2f);

    particleEfect->setLifeTime(5000.0f);
    particleEfect->setLifeTimeDiff(2500.0f);
}

void Entity::onUpdate(float dt)
{
    //states

    //seek
    if (state == EntityState::Seek)
    {
        if (isPlayerInVisionRange()) {
            state = EntityState::Attack;
        }

        seek(dt);
    }
    //attack
    else if (state == EntityState::Attack)
    {
        if (!isPlayerInVisionRange()) {
            state = EntityState::Seek;
        }

        attack(dt);
    }
    //sleep
    else
    {
        if (isPlayerInVisionRange()) {
            state = EntityState::Attack;
        }
    }


    //anims

    if (getTransformPtr()->inMove())
    {
        animController->play(ANIM_RUN);
    }
    else
    {
        animController->play(ANIM_IDLE);

    }


    //flip

    if (state == EntityState::Seek)
    {
        bool flip = (getTransformPtr()->get_position().x - getTransformPtr()->get_prePosition().x) >= 0.0f;
        getTransformPtr()->set_flip_x(flip);
        weaponCore->getTransformPtr()->set_flip_x(!flip);
    }
    else if (state == EntityState::Attack)
    {
        bool flip = (player->get_position().x - getTransformPtr()->get_position().x) >= 0.0f;
        getTransformPtr()->set_flip_x(flip);
        weaponCore->getTransformPtr()->set_flip_x(!flip);
    }

    if (healthBar && healthBar->getTransformPtr())
    {
        healthBar->getTransformPtr()->set_flip_x(getTransformPtr()->get_flipX());
        healthBar->refresh();
    }
}

void Entity::onDestroy()
{
    if (particleEfect && particleEfect->getTransformPtr())
    {
        particleEfect->getTransformPtr()->set_position(getTransformPtr()->get_position());
        particleEfect->invoke(Vector2(0.0f, -1.0f), false);
    }
}



void Entity::set(const EntityData& data)
{
    this->addTag(Tag::ENEMY.data());

    //data
    this->entityData = data;

    uniform_real_distribution<float> rndSpeed(data.runSpeed - (0.2 * data.runSpeed), data.runSpeed + (0.2 * data.runSpeed));
    this->entityData.runSpeed = rndSpeed(rng);

    uniform_real_distribution<float> rndScale(data.scale - (0.1 * data.scale), data.scale + (0.1 * data.scale));
    this->entityData.scale = rndScale(rng);


    float health = 0.0f;
    float strength = 0.0f;
    EntitySO::getStats(data.attribute, health, strength);

    if (health == 0.0f || strength == 0.0f) {
        VDebuger::print("<ERROR> ENTITY :: SET :: loading attributes error");
    }


    if (healthSystem)
    {
        uniform_real_distribution<float> rndHealth(health - (0.1 * health), health + (0.1 * health));
        healthSystem->setHealth(rndHealth(rng));
    }
    else
    {
        VDebuger::print("<ERROR> ENTITY :: SET :: health system is nullptr");
    }



    if (particleEfect)
    {
        particleEfect->setParticleNum(healthSystem->getHealthMax() / 2.0f);
        particleEfect->setParticleNumDiff(0u);
    }



    if (!getGame()) {
        VDebuger::print("<ERROR> ENTITY :: SET :: object is not inited");
    }



    body->getSpritePtr()->setTexture(data.textureRef);

    weaponCore = Weapon::createWeapon(getGame()->get_currentScene(),
                                      *WeaponSO::get(data.weaponID),
                                      Tag::PLAYER_CORE.data(),
                                      getRenderLayer()+1u,
                                      hand);
    weaponCore->getSpritePtr()->setRenderWithLocalFlip(true);




    if (weaponCore)
    {
        uniform_real_distribution<float> rndStrength(strength - (0.1 * strength), strength + (0.1 * strength));
        weaponCore->scaleDamage(rndStrength(rng) / weaponCore->getData().damage);
    }
    else
    {
        VDebuger::print("<ERROR> ENTITY :: SET :: weapon core is nullptr");
    }




    body->getTransformPtr()->scaleBy(this->entityData.scale);
    hand->getTransformPtr()->add_position(2.5f * this->entityData.scale, -5.0f * this->entityData.scale);

    this->collider->set(body->getSpritePtr()->getTextureRect().width * body->getTransformPtr()->get_scale().x,
                        body->getSpritePtr()->getTextureRect().height * body->getTransformPtr()->get_scale().y);




    if (healthBar)
    {
        healthBar->setValueMax(healthSystem->getHealthMax());
        healthBar->setValue(healthSystem->getHealth());

        auto t = healthBar->getTransformPtr();
        if (t && body && body->getSpritePtr())
        {
            t->add_position(Vector2(0.0f, 15.0f + (body->getSpritePtr()->getTextureRect().height) * this->entityData.scale));
        }
    }
    else
    {
        VDebuger::print("<ERROR> ENTITY :: SET :: healthBar is nullptr");
    }




    //anims
    {
        //AnimationCycle cycle_idle({am_idle1, am_idle2});

        auto am_idle = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_scale(),
                                                           body->getTransformPtr()->get_scale(),
                                                           body->getTransformPtr()->get_rotation(),
                                                           body->getTransformPtr()->get_rotation(),
                                                           1.f);

        AnimationCycle cycle_idle({am_idle});
        Animation anim_idle({cycle_idle});


        auto am_run1 = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_scale(),
                                                           body->getTransformPtr()->get_scale(),
                                                           getTransformPtr()->get_rotation() - 4.f,
                                                           getTransformPtr()->get_rotation() + 4.f,
                                                           1.f/data.runSpeed);

        auto am_run2 = make_shared<AnimationTransformStep>(body->getTransformPtr(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_localPosition(),
                                                           body->getTransformPtr()->get_scale(),
                                                           body->getTransformPtr()->get_scale(),
                                                           body->getTransformPtr()->get_rotation() + 4.f,
                                                           body->getTransformPtr()->get_rotation() - 4.f,
                                                           1.f/data.runSpeed);

        AnimationCycle cycle_run({am_run1, am_run2});
        Animation anim_run({cycle_run});


        ANIM_IDLE = animController->add(anim_idle);
        ANIM_RUN = animController->add(anim_run);
    }
}



///
/// states
///

void Entity::seek(const float& dt)
{
    timeAcc += dt;

    if (timeAcc >= nextTime)
    {
        //random direction
        uniform_real_distribution<float> dist(-1.f, 1.f);
        rndDirection = Vector2(dist(rng), dist(rng));
        rndDirection.normalize();

        //random time
        uniform_real_distribution<float> rndDist(Parameters::get_entity_rndMoveIntense() - 2.f, Parameters::get_entity_rndMoveIntense() + 2.f);
        rnd = rndDist(rng);

        //time to next update
        nextTime = timeAcc + rnd;
    }

    if (move(rndDirection, entityData.walkSpeed, dt))
    {
        nextTime = 0.0f;
        timeAcc = 0.0f;
    }
}


///
/// helpers
///

float Entity::distanceToPlayer() {
    return getTransformPtr()->get_position().distanceToLite(player->get_position());
}

bool Entity::isPlayerInVisionRange()
{
    return
        !Rycast::hit(tilemap, getTransformPtr()->get_position(), player->get_position());
}

bool Entity::isPlayerInWeaponRange()
{
    if (!weaponCore) {
        return false;
    }

    return distanceToPlayer() <= weaponCore->getRange()*weaponCore->getRange();
}

bool Entity::move(const Vector2& direction, const float& speed, const float& dt)
{
    Vector2 _vec = direction.get_normalized() * speed * 0.075f * dt;
    bool rycastHit = Rycast::hit(tilemap, getTransformPtr()->get_position(), getTransformPtr()->get_position() + _vec);

    if (!rycastHit) {
        rb->addForce(_vec);
    }

    return rycastHit;
}

bool Entity::moveTo(const Vector2& point, const float& speed, const float& dt)
{
    Vector2 dir = point - getTransformPtr()->get_position();
    return move(dir, speed, dt);
}
