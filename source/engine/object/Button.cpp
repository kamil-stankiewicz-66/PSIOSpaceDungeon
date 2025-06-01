#include "engine/object/Button.h"
#include "engine/component/Collider.h"
#include "engine/core/Input.h"
#include "engine/component/Renderable.h"



///
/// AbstractButton
///


AbstractButton::AbstractButton() : collider(nullptr)
{
    //colors
    this->normalColor = Color::White;
    this->highlightedColor = Color::White;
    this->pressedColor = Color::White;
}

void AbstractButton::onAwake()
{
    collider = createComponent<BoxCollider>();
}

void AbstractButton::onUpdate(float deltaTime)
{
    if (!collider) {
        return;
    }

    if (collider->isThisPointInCollider(Input::Mouse::AXIS()))
    {
        this->setColor(highlightedColor);

        if (Input::Mouse::LEFT_BUTTON())
        {
            this->setColor(pressedColor);
            this->onClick(deltaTime);
        }
    }
    else
    {
        this->setColor(normalColor);
    }
}



//private setter

void AbstractButton::setColor(const Color& _color)
{
    if (!sprite) {
        return;
    }

    sprite->setColor(_color);
}



//public setters

void AbstractButton::set_normalColor(const Color& _color) {
    this->normalColor = _color;
}

void AbstractButton::set_pressedColor(const Color& _color) {
    this->pressedColor = _color;
}

void AbstractButton::set_highlightedColor(const Color& _color) {
    this->highlightedColor = _color;
}

void AbstractButton::set_reactionAreaSize(const float& x, const float& y)
{
    if (!collider) {
        return;
    }

    collider->set(x, y);
}






///
/// Button
///


void Button::onClick(float) {
    VEvent::invoke();
}

void Button::addListener(const std::function<void()>& newListener) {
    VEvent::addListener(newListener);
}
