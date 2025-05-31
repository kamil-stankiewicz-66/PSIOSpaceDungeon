#include "game/ui/BasicButtons.h"
#include "engine/component/Sprite.h"
#include "game/core/Asset.h"

void MenuButton::onAwake()
{
    ActionButton::onAwake();

    set_normalColor(Color::Red);
    set_highlightedColor(Color(0,200,0,255));
    set_pressedColor(Color::Yellow);


    if (!transform || !sprite) {
        return;
    }

    sprite->setTexture(Asset::Graphics::BUTTON.data());

    transform->scaleBy(Vector2(0.3f, 1.f));
    set_reactionAreaSize(280.f, 95.0f);
}
