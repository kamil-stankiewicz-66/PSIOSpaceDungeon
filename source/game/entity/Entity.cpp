#include "game/entity/Entity.h"
#include "engine/core/Engine.h"
#include "game/core/Parameter.h"
#include "game/core/Tag.h"
#include "game/physics/Rycast.h"

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


    //parts
    hand = getGame()->get_currentScene()->createObject<GameObject>();
    this->addChild(hand);


    //componets
    collider = createComponent<BoxCollider>();;

    rb = createComponent<Rigidbody>();
    rb->init(getTransformPtr(), getTransformPtr());

    animController = createComponent<AnimationController>();


    //find objects
    player = getGame()->get_currentScene()->findGameObject(Tag::PLAYER_RECT.data())->getTransformPtr();
    tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());

    if (!player || !tilemap) {
        VDebuger::print("<ERROR> :: ENTITY :: player or tilemap is nullptr");
    }
}

void Entity::onUpdate(float dt)
{
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
}



void Entity::set(const EntityData& data)
{
    this->addTag(Tag::ENEMY.data());

    //data
    this->entityData = data;

    uniform_real_distribution<float> rndSpeed(data.runSpeed - (0.1 * data.runSpeed), data.runSpeed + (0.1 * data.runSpeed));
    this->entityData.runSpeed = rndSpeed(rng);

    uniform_real_distribution<float> rndScale(data.scale - (0.1 * data.scale), data.scale + (0.1 * data.scale));
    this->entityData.scale = rndScale(rng);



    if (!getGame()) {
        VDebuger::print("<ERROR> ENTITY :: SET :: object is not inited");
    }


    getSpritePtr()->setTexture(data.textureRef);

    weaponCore = Weapon::createWeapon(getGame()->get_currentScene(),
                                      *WeaponSO::get(data.weaponID),
                                      Tag::PLAYER_CORE.data(),
                                      getRenderLayer()+1u,
                                      hand);

    this->getTransformPtr()->scaleBy(this->entityData.scale);
    hand->getTransformPtr()->add_position(2.5f * this->entityData.scale, -5.0f * this->entityData.scale);

    this->collider->set(this->getSpritePtr()->getTextureRect().width * this->entityData.scale,
                        this->getSpritePtr()->getTextureRect().height * this->entityData.scale);
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
