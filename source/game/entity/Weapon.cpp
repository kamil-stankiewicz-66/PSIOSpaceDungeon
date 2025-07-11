#include "game/entity/Weapon.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"
#include "game/core/Parameter.h"
#include "game/core/Tag.h"
#include "game/effect/AudioPlayer.h"
#include "game/effect/ParticleEffect.h"
#include "game/entity/HealthSystem.h"
#include <cmath>



///
/// Weapon
///

void Weapon::onUpdate(float dt)
{
    if (timeAcc <= data.attackTimeOut) {
        timeAcc += dt;
    }
}

void Weapon::attack()
{
    if (data.attackTimeOut <= timeAcc)
    {
        this->attackCore();
        timeAcc = 0.0f;

        //sound
        auto audioPlayer = getGame()->get_currentScene()->createObject<AudioPlayer>();
        audioPlayer->init(data.attackSoundRef, Parameters::get_sound_volume_effects(), true);
        audioPlayer->play();
    }
}


void Weapon::set(const WeaponData& data, const string& targetTag)
{
    this->data = data;

    if (!data.textureRef.empty()) {
        getSpritePtr()->setTexture(TextureBase::get(data.textureRef));
    }

    this->targetTag = targetTag;
}


void Weapon::scaleDamage(const float& factor)
{
    data.damage += factor;
}


const float& Weapon::getRange() const {
    return this->data.range;
}

const WeaponData& Weapon::getData() const {
    return this->data;
}

const string& Weapon::getTargetTag() const {
    return this->targetTag;
}



//static
Weapon* Weapon::createWeapon(Scene* scene, const WeaponData& data, const string& targetTag,
                                uint renderLayer, Object* parent)
{
    if (!scene) {
        VDebuger::print("<ERROR> WEAPON :: CREATE_WEAPON :: scene is nullptr");
        return nullptr;
    }

    //empty ptr
    Weapon* weapon = nullptr;

    //create object
    switch (data.type)
    {
    case WeaponData::Type::Melee:
        weapon = scene->createObject<Melee>(renderLayer, parent);
        break;
    case WeaponData::Type::Gun:
        weapon = scene->createObject<Gun>(renderLayer, parent);
        break;
    default:
        return nullptr;
        break;
    }

    //init
    if (weapon) {
        weapon->set(data, targetTag);
    }

    return weapon;
}




///
/// Melee
///

void Melee::set(const WeaponData& data, const string& targetTag)
{
    Weapon::set(data, targetTag);
    collider = createComponent<CircleCollider>();
    collider->set(data.range);
}

void Melee::attackCore()
{
    if (!collider) {
        VDebuger::print("<ERROR> MELEE :: ATACK_CORE :: collider is nullptr");
        return;
    }

    //damage
    auto collisions = collider->getCollisions();
    for (auto it = collisions.begin(); it != collisions.end(); ++it)
    {
        Collider* coll = *it;

        if (!coll) {
            continue;
        }

        Object* obj = coll->getObject();

        if (!obj) {
            continue;
        }

        //if this is not target skip
        if (!obj->checkTag(this->getTargetTag())) {
            continue;
        }

        if (auto healthSys = obj->getComponent<HealthSystem>(true)) {
            healthSys->addDamage(getData().damage);
        }
    }
}

void Melee::aim(const Vector2& point)
{

}

void Melee::resetAim()
{

}



///
/// Gun
///

void Gun::attackCore()
{
    //create
    Bullet* bullet = getGame()->get_currentScene()->createObject<Bullet>(getRenderLayer()-1);

    if (aimDir.zero()) {
        aimDir.x = getTransformPtr()->get_flipX() ? -1.0f : 1.0f;
    }

    //transform
    bullet->getTransformPtr()->set_position(getTransformPtr()->get_position() + (aimDir*50.f));
    bullet->getTransformPtr()->set_rotation(getTransformPtr()->get_rotation());
    bullet->getTransformPtr()->set_flip_x(getTransformPtr()->get_localFlipX());

    //add texture
    bullet->getSpritePtr()->setTexture(TextureBase::get(Asset::Graphics::LASER_BULLET.data()));
    bullet->getSpritePtr()->setRenderWithLocalFlip(true);

    //init
    bullet->init(getData().damage, aimDir, this->getTargetTag(), tilemap);
}

void Gun::set(const WeaponData& data, const string& targetTag)
{
    Weapon::set(data, targetTag);

    tilemap = getGame()->get_currentScene()->findObject<Tilemap>(Tag::TILEMAP.data());
    if (!tilemap) {
        VDebuger::print("<ERROR> :: GUN :: tilemap is nullptr");
    }
}

void Gun::aim(const Vector2& point)
{
    aimDir = Vector2(point - getTransformPtr()->get_position());
    aimDir.normalize();

    float aimAngle = atan2(aimDir.y, aimDir.x) * (180.0 / M_PI);

    if (getTransformPtr()->get_localFlipX()) {
        aimAngle = 180.0 - aimAngle;
    }

    getTransformPtr()->set_rotation(-static_cast<float>(aimAngle));
}

void Gun::resetAim() {
    getTransformPtr()->set_rotation(0.0f);
    aimDir.clear();
}


//bullet

void Bullet::init(const float& damage, const Vector2& dir, const string& targetTag, Tilemap* tilemap)
{
    this->damage = damage;
    this->dir = dir;
    this->targetTag = targetTag;
    this->tilemap = tilemap;

    getSpritePtr()->setColor(sf::Color::Yellow);
    getTransformPtr()->scaleBy(0.2f);

    collider = createComponent<CircleCollider>();
    collider->set(10.0f);
}

void Bullet::destroy(const sf::Color& color)
{
    //effect
    effect(color);

    //destroy
    getGame()->get_currentScene()->killObject(this, true);
}

void Bullet::effect(const sf::Color& color)
{
    auto parEff = getGame()->get_currentScene()->createObject<ParticleEffect>(getRenderLayer());
    parEff->addTag("particle_effect");
    parEff->getTransformPtr()->set_position(getTransformPtr()->get_position());

    parEff->setTexture(Asset::Graphics::PARTICLE.data());

    if (sf::Color::Red == color)
    {
        parEff->setColor(color);
        parEff->setScale(Vector2(0.02f, 0.08f));

        parEff->setSpread(90.0f);

        parEff->setSpeed(9.0f);
        parEff->setSpeedDiff(8.5f);

        parEff->setLifeTime(250.0f);
        parEff->setLifeTimeDiff(249.0f);

        parEff->setParticleNum(100u);
        parEff->setParticleNumDiff(50u);
    }
    else
    {
        parEff->setColor(color);
        parEff->setScale(Vector2(0.02f, 0.01f));

        parEff->setSpread(90.0f);

        parEff->setSpeed(4.0f);
        parEff->setSpeedDiff(3.5f);

        parEff->setLifeTime(100.0f);
        parEff->setLifeTimeDiff(30.0f);

        parEff->setParticleNum(20u);
        parEff->setParticleNumDiff(4u);
    }

    parEff->invoke(dir * -1.0f);
}

void Bullet::onUpdate(float dt)
{
    //move
    getTransformPtr()->add_position(dir * 0.075 * dt * Parameters::get_bullet_speed());

    //damage
    auto collisions = collider->getCollisions();
    for (auto it = collisions.begin(); it != collisions.end(); ++it)
    {
        Collider* coll = *it;

        if (!coll) {
            continue;
        }

        Object* obj = coll->getObject();

        if (!obj) {
            continue;
        }

        //if this is not target skip
        if (!obj->checkTag(this->targetTag)) {
            continue;
        }

        if (auto healthSys = obj->getComponent<HealthSystem>(true)) {
            healthSys->addDamage(damage);
        }

        this->destroy(sf::Color::Red);
    }

    //collision with tilemap
    if (tilemap)
    {
        auto tile = tilemap->getTileRealPos(getTransformPtr()->get_position().x, getTransformPtr()->get_position().y);

        if (!tile || tile->getExceedability() <= 0.0f) {
            this->destroy(sf::Color::Yellow);
        }
    }
}
