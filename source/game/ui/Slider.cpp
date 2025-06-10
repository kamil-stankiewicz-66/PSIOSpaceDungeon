#include "game/ui/Slider.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"


void Slider::onAwake()
{
    background = getGame()->get_currentScene()->createObject<SpriteObject>(getRenderLayer());
    slider = getGame()->get_currentScene()->createObject<SpriteObject>(getRenderLayer()+1u);

    background->getSpritePtr()->setTexture(Asset::Graphics::HEALTHBAR.data());
    slider->getSpritePtr()->setTexture(Asset::Graphics::HEALTHBAR.data());

    background->getSpritePtr()->setRenderWithLocalFlip(true);
    slider->getSpritePtr()->setRenderWithLocalFlip(true);

    this->addChild(background);
    this->addChild(slider);
}


void Slider::refresh()
{
    if (valueMax == 0.0f) {
        return;
    }

    if (!this->getTransformPtr() || !background->getTransformPtr() || !slider->getTransformPtr())
    {
        VDebuger::print("<ERROR> SLIDER :: REFRESH :: slider is not inited");
        return;
    }


    float fill = (value / valueMax);
    slider->getTransformPtr()->set_scale(Vector2(fill * background->getTransformPtr()->get_scale().x, slider->getTransformPtr()->get_scale().y));
    float diff = getWidth() * 0.5f * (1 - fill);

    bool flip = this->getTransformPtr()->get_flipX();
    slider->getTransformPtr()->set_position(diff * (flip ? 1.0f : -1.0f));
}


void Slider::init(bool rect)
{
    if (this->getTransformPtr() && background->getTransformPtr() && slider->getTransformPtr())
    {
        return;
    }

    if (rect)
    {
        this->createComponent<RectTransform>();
        background->createComponent<RectTransform>();
        slider->createComponent<RectTransform>();
    }
    else
    {
        this->createComponent<Transform>();
        background->createComponent<Transform>();
        slider->createComponent<Transform>();
    }
}


void Slider::setValue(const float& v)
{
    value = v;

    if (value > valueMax)
    {
        value = valueMax;
    }
    else if (value < 0.0f)
    {
        value = 0.0f;
    }

    refresh();
}

void Slider::setValueMax(const float& v)
{
    valueMax = v;

    if (value > valueMax)
    {
        value = valueMax;
    }
    else if (valueMax < 0.0f)
    {
        valueMax = 0.0f;
    }

    refresh();
}


void Slider::setFillColor(const sf::Color& color)
{
    if (auto sprite = slider->getSpritePtr())
    {
        sprite->setColor(color);
    }
}

void Slider::setBackgroundColor(const sf::Color& color)
{
    if (auto sprite = background->getSpritePtr())
    {
        sprite->setColor(color);
    }
}

void Slider::scaleWidth(const float& v)
{
    if (!background->getTransformPtr() || !slider->getTransformPtr()) {
        return;
    }

    background->getTransformPtr()->set_scale(Vector2(v, background->getTransformPtr()->get_scale().y));
    slider->getTransformPtr()->set_scale(Vector2(v, slider->getTransformPtr()->get_scale().y));
    refresh();
}

void Slider::scaleHeight(const float& v)
{
    if (!background->getTransformPtr() || !slider->getTransformPtr()) {
        return;
    }

    background->getTransformPtr()->set_scale(Vector2(background->getTransformPtr()->get_scale().x, v));
    slider->getTransformPtr()->set_scale(Vector2(slider->getTransformPtr()->get_scale().x, v));
    refresh();
}


const float& Slider::getValue() const {
    return this->value;
}

const float& Slider::getValueMax() const {
    return this->valueMax;
}


const float Slider::getWidth() const
{
    if (!background->getTransformPtr() || !background->getSpritePtr()) {
        return 0.0f;
    }

    return background->getSpritePtr()->getTextureRect().width * background->getTransformPtr()->get_scale().x;
}

const float Slider::getHeight() const
{
    if (!background->getTransformPtr() || !background->getSpritePtr()) {
        return 0.0f;
    }

    return background->getSpritePtr()->getTextureRect().height * background->getTransformPtr()->get_scale().y;
}
