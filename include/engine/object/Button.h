#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics/Color.hpp"
#include "engine/object/Object.h"
#include "engine/core/Event.h"

using Color = sf::Color;
class BoxCollider;

///
/// \brief A class representing a basic abstract button.
///

class AbstractButton : public UIObject
{
private:
    BoxCollider* collider;

    Color normalColor;
    Color pressedColor;
    Color highlightedColor;

    bool m_isPressed = false;

protected:
    void onAwake() override;
    void onUpdate(float) override;

    void setColor(const Color&);

    ///
    /// \brief The method executed when the button is clicked.
    ///

    virtual void onClick(float deltaTime) = 0;

public:
    AbstractButton();
    void set_normalColor(const Color&);
    void set_pressedColor(const Color&);
    void set_highlightedColor(const Color&);
    void set_reactionAreaSize(const float& x, const float& y);
};

///
/// \brief A class representing a button.
/// \details Button invoke event automaticly when pressed.
///

class Button : public AbstractButton, private VEvent
{
private:
    void onClick(float) override; //This method is called by the engine.

public:

    ///
    /// \brief Adds a function that the button will execute when pressed.
    /// \param newListener
    ///

    void addListener(const std::function<void()>& newListener);


    ///
    /// \brief Reset.
    ///

    void dispose();
};

#endif // BUTTON_H
