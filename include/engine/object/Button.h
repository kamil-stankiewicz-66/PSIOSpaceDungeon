#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics/Color.hpp"
#include "engine/object/Object.h"
#include <functional>

using Color = sf::Color;
class BoxCollider;

///
/// \brief A class representing a basic abstract button.
///

class Button : public UIObject
{
private:
    BoxCollider* collider;

    Color normalColor;
    Color pressedColor;
    Color highlightedColor;

protected:
    void onAwake() override;
    void onUpdate(float) override;

    void setColor(const Color&);

    ///
    /// \brief The method executed when the button is clicked.
    ///

    virtual void onClick(float deltaTime) = 0;

public:
    Button();
    void set_normalColor(const Color&);
    void set_pressedColor(const Color&);
    void set_highlightedColor(const Color&);
    void set_reactionAreaSize(float x, float y);
};

///
/// \brief Button with function.
/// \details Button executes function automaticly when pressed.
///

class ActionButton : public Button
{
private:

    //stores the function that will execute onClick
    std::function<void()> action;

    //method called by the engine
    void onClick(float) override;

public:

    ///
    /// \brief Sets the function that the button will execute when pressed.
    /// \param _action This function will be called when the button is pressed.
    ///

    void setAction(std::function<void()> _action);
};

#endif // BUTTON_H
