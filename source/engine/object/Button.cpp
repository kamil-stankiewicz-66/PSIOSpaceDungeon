#include "engine/object/Button.h"
#include "engine/component/Collider.h"
#include "engine/core/Input.h"
#include "engine/component/Sprite.h"

Button::Button() : collider(nullptr) {}

void Button::onAwake()
{
    collider = createComponent<BoxCollider>();
}

void Button::onUpdate(float deltaTime)
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


///
/// private setter
///

void Button::setColor(const Color& _color)
{
    if (!sprite) {
        return;
    }

    sprite->setColor(_color);
}


///
/// public setters
///

void Button::set_normalColor(const Color& _color) {
    this->normalColor = _color;
}

void Button::set_pressedColor(const Color& _color) {
    this->pressedColor = _color;
}

void Button::set_highlightedColor(const Color& _color) {
    this->highlightedColor = _color;
}

void Button::set_reactionAreaSize(float x, float y)
{
    if (!collider) {
        return;
    }

    collider->set(x, y);
}
