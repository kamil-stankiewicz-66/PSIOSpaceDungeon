#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>
#include "engine\core\Vector2.h"

///
/// \brief Class handling input data from keyboard and mouse.
///

class Input
{
friend class Engine;

private:
    static sf::RenderWindow* window; //Pointer to the SFML window, used to get the mouse position

    static void init(sf::RenderWindow* win);  //This method is called by the engine.
    static void update(); //Input data update – This method is called by the engine.

public:

    ///
    /// \brief Class handling input data from keyboard.
    ///

    using Keyboard = sf::Keyboard;

    ///
    /// \brief Class handling input data from mouse.
    ///

    class Mouse
    {
    friend class Input;

    private:

        //Stores the current cursor position relative to the center of the window.
        static Vector2 pos;

        //Update mouse position.
        static void update();

    public:

        ///
        /// \brief Method returns current cursor position in window.
        /// \details When cursor is at window center, its position is (0, 0).
        ///

        static const Vector2& AXIS();

        ///
        /// \brief Method returns true if left mouse button was pressed.
        /// \return bool
        ///

        static bool LEFT_BUTTON();

        ///
        /// \brief Method returns true if right mouse button was pressed.
        /// \return bool
        ///

        static bool RIGHT_BUTTON();
    };

};


#endif // INPUT_H

