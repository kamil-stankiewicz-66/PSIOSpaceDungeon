#include "game/entity/Weapon.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"
#include <cmath>

const float& Weapon::getRange() const {
    return this->range;
}


void Bullet::init(const float& damage, const float& rotation, bool flip)
{
    this->damage = damage;
    getTransformPtr()->set_rotation(rotation);

    float r = rotation;
    if (flip) {
        r += 180.f;
    }

    float radians = r * M_PI / 180.0f;
    dir.x = cos(radians);
    dir.y = sin(radians);

    dir.normalize();

    getSpritePtr()->setTexture(Asset::Graphics::BUTTON.data());
    getSpritePtr()->setColor(sf::Color::Yellow);
    getTransformPtr()->set_scale(Vector2(0.75f, 1.0f));
    getTransformPtr()->scaleBy(0.025f);
}

void Bullet::onUpdate(float dt)
{
    getTransformPtr()->add_position(dir * 0.075 * dt * speed);
}


void AssaultRifle::attack()
{
    auto bullet = getGame()->get_currentScene()->createObject<Bullet>();
    bullet->init(damage, getTransformPtr()->get_rotation(), getTransformPtr()->get_flipX());
    bullet->getTransformPtr()->set_position(getTransformPtr()->get_position());
}
