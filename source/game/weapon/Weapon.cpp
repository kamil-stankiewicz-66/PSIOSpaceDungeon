#include "game/weapon/Weapon.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"
#include "game/core/Parameter.h"
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
    if (data.attackTimeOut <= timeAcc) {
        this->attackCore();
        timeAcc = 0.0f;
    }
}


void Weapon::set(const WeaponData& data)
{
    this->data = data;
    getSpritePtr()->setTexture(data.textureRef);
}


const float& Weapon::getRange() const {
    return this->data.range;
}

const WeaponData& Weapon::getData() const {
    return data;
}



///
/// Melee
///

void Melee::attackCore()
{
    auto collisions = collider->getCollisions();

    for (auto it = collisions.begin(); it != collisions.end(); ++it)
    {
        //Collider* coll = *it;
        //* obj = coll->getObject();

        //add damage
    }
}



///
/// Gun
///

void Gun::attackCore()
{
    Bullet* bullet = getGame()->get_currentScene()->createObject<Bullet>(getRenderLayer()-1);

    if (aimDir.zero()) {
        aimDir.x = getTransformPtr()->get_flipX() ? -1.0f : 1.0f;
    }

    bullet->getTransformPtr()->set_position(getTransformPtr()->get_position() + (aimDir*50.f));
    bullet->getTransformPtr()->set_rotation(getTransformPtr()->get_rotation());
    bullet->getTransformPtr()->set_flip_x(getTransformPtr()->get_flipX());

    bullet->getSpritePtr()->setTexture(bulletTxt);
    bullet->init(getData().damage, aimDir);
}

void Gun::set(const WeaponData& data)
{
    Weapon::set(data);

    bulletTxt = make_shared<sf::Texture>();
    if (!bulletTxt->loadFromFile(Asset::Graphics::LASER_BULLET.data())) {
        VDebuger::print("<ERROR> :: GUN :: texture load error");
    }
}

void Gun::aim(const Vector2& point)
{
    aimDir = Vector2(point - getTransformPtr()->get_position());
    aimDir.normalize();

    float aimAngle = atan2(aimDir.y, aimDir.x) * (180.0 / M_PI);

    if (getTransformPtr()->get_flipX()) {
        aimAngle = 180.0 - aimAngle;
    }

    getTransformPtr()->set_rotation(-static_cast<float>(aimAngle));
}

void Bullet::init(const float& damage, const Vector2& dir)
{
    this->damage = damage;
    this->dir = dir;

    getSpritePtr()->setColor(sf::Color::Yellow);
    getTransformPtr()->scaleBy(0.2f);
}

void Bullet::onUpdate(float dt)
{
    getTransformPtr()->add_position(dir * 0.075 * dt * Parameters::get_bullet_speed());
}
