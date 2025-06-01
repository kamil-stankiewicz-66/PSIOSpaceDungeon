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

    getSpritePtr()->setTexture(Asset::Graphics::BUTTON.data());

    transform->scaleBy(Vector2(1.f, 1.2f));
    set_reactionAreaSize(280.f, 95.0f);


    //text
    auto textObj = this->getGame()->get_currentScene()->createObject<TextObject>();
    this->addChild(textObj);

    textObj->getTextPtr()->setFont(Asset::Fonts::PIXEL_OPERATOR_8_BOLD.data());
    textObj->getTextPtr()->setText("Play");
    textObj->getTextPtr()->setCharacterSize(50);
    textObj->getTextPtr()->setLetterSpacing(0.5f);
}
