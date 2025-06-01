#include "engine/component/Transform.h"
#include "engine/object/Object.h"

#include <cmath>





///
/// Transform
///


void Transform::onUpdate(float _dt)
{
    this->m_inMove = this->position != this->pre_position;
    this->pre_position = this->position;
}


Transform::Transform(const Vector2& arg_position,
                     const Vector2& arg_scale,
                     const float& arg_rotation,
                     const bool arg_flipX)
    : Component(COMPONENT_PRIORITY::TRANSFORM), m_rect(false), m_inMove(true)
{
    this->position = arg_position;
    this->pre_position = this->position;
    this->scale = arg_scale;
    this->rotation = arg_rotation;
    this->flip_x = arg_flipX;
}

Transform::~Transform() {}


void Transform::makeRect()
{
    this->m_rect = true;
}


void Transform::updateGlobalTransform()
{
    this->set_position(this->get_position());
    this->scale = this->get_scale();
    this->set_flip_x(this->get_flipX());
}

void Transform::resetPosition()
{
    this->set_position(Vector2());
}

void Transform::scaleBy(const Vector2& _v)
{
    this->scale = this->scale * _v;
}

void Transform::scaleBy(const float& _v)
{
    this->scale = this->scale * Vector2(_v, _v);
}



// setters

void Transform::set_position(const Vector2& _v)
{
    this->position = _v;
}

void Transform::add_position(const Vector2& _v)
{
    this->set_position(this->position + _v);
}

void Transform::set_rotation(const float& _v)
{
    this->rotation = std::fmod(_v, 360.0f);
}

void Transform::add_rotation(const float& _v)
{
    this->set_rotation(this->rotation + _v);
}

void Transform::set_flip_x(const bool f)
{
    this->flip_x = f;
}



// getters

const Vector2 Transform::get_position() const
{
    if (!this->getObject()->isChild())
    {
        return this->position;
    }

    if (!this->getObject()->getParent()->transform->get_flipX())
    {
        return this->getObject()->getParent()->transform->get_position() + this->position;
    }
    else
    {
        return Vector2(
            this->getObject()->getParent()->transform->get_position().x - this->position.x,
            this->getObject()->getParent()->transform->get_position().y + this->position.y
            );
    }
}

const Vector2& Transform::get_prePosition() const {
    return this->pre_position;
}

const Vector2& Transform::get_scale() const
{
    return this->scale;
}

const float& Transform::get_rotation() const
{
    return this->rotation;
}

const bool Transform::get_flipX() const
{
    if (this->getObject()->isChild())
    {
        return this->getObject()->getParent()->transform->get_flipX();
    }

    return this->flip_x;
}



// info


const bool Transform::isRect() const
{
    return this->m_rect;
}

const float Transform::get_speed() const
{
    return (const float)
    sqrt(std::pow(this->position.x - this->pre_position.x, 2)
         + std::pow(this->position.y - this->pre_position.y, 2))
        ;
}

const bool Transform::inMove() const {
    return this->m_inMove;
}





///
/// RectTransform
///


RectTransform::RectTransform(const Vector2& arg_position,
                             const Vector2& arg_scale,
                             const double& arg_rotation,
                             const bool arg_flipX)
    : Transform(arg_position, arg_scale, arg_rotation, arg_flipX)
{
    this->makeRect();
}
