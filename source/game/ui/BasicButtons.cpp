#include "game/ui/BasicButtons.h"
#include "engine/component/Renderable.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"

void MenuButton::onAwake()
{
    Button::onAwake();

    set_normalColor(Color::Red);
    set_highlightedColor(Color(0,200,0,255));
    set_pressedColor(Color::Yellow);


    if (!getTransformPtr() || !getSpritePtr()) {
        return;
    }

    getSpritePtr()->setTexture(TextureBase::get(Asset::Graphics::BUTTON.data()));

    transform->scaleBy(Vector2(1.f, 1.2f));
    set_reactionAreaSize(280.f, 95.0f);


    //text
    textObj = this->getGame()->get_currentScene()->createObject<TextObject>(getRenderLayer()+1u);
    this->addChild(textObj);

    textObj->getTextPtr()->setFont(FontBase::get(Asset::Fonts::BANGERS.data()));
    textObj->getTextPtr()->setCharacterSize(50);
}

void MenuButton::setText(const string& text)
{
    if (!textObj) {
        return;
    }

    textObj->getTextPtr()->setText(text);
}

TextObject* MenuButton::getTextObj() const {
    return textObj;
}
