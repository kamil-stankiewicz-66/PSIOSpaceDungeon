#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics/Color.hpp"
#include "engine/object/Object.h"

using Color = sf::Color;
class BoxCollider;

///
/// \brief Klasa reprezentujaca podstawowy przycisk.
///

class Button : public UIObject
{
private:
    BoxCollider* collider;

    Color normalColor;
    Color pressedColor;
    Color highlightedColor;

    void onAwake() override;
    void onUpdate(float) override;

    void setColor(const Color&);

protected:

    ///
    /// \brief Metoda wykonywana po kliknieciu w przycisk.
    ///

    virtual void onClick(float deltaTime) = 0;

public:
    Button();
    void set_normalColor(const Color&);
    void set_pressedColor(const Color&);
    void set_highlightedColor(const Color&);
    void set_reactionAreaSize(float x, float y);
};


#endif // BUTTON_H
