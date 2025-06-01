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

    class Keyboard
    {

    public:

        ///
        /// \brief Enum storing the numbers of selected keyboard buttons, compatible with SFML.
        ///

        enum class Key {
            A = sf::Keyboard::A, B = sf::Keyboard::B, C = sf::Keyboard::C, D = sf::Keyboard::D,
            E = sf::Keyboard::E, F = sf::Keyboard::F, G = sf::Keyboard::G, H = sf::Keyboard::H,
            I = sf::Keyboard::I, J = sf::Keyboard::J, K = sf::Keyboard::K, L = sf::Keyboard::L,
            M = sf::Keyboard::M, N = sf::Keyboard::N, O = sf::Keyboard::O, P = sf::Keyboard::P,
            Q = sf::Keyboard::Q, R = sf::Keyboard::R, S = sf::Keyboard::S, T = sf::Keyboard::T,
            U = sf::Keyboard::U, V = sf::Keyboard::V, W = sf::Keyboard::W, X = sf::Keyboard::X,
            Y = sf::Keyboard::Y, Z = sf::Keyboard::Z,

            Num0 = sf::Keyboard::Num0, Num1 = sf::Keyboard::Num1, Num2 = sf::Keyboard::Num2,
            Num3 = sf::Keyboard::Num3, Num4 = sf::Keyboard::Num4, Num5 = sf::Keyboard::Num5,
            Num6 = sf::Keyboard::Num6, Num7 = sf::Keyboard::Num7, Num8 = sf::Keyboard::Num8,
            Num9 = sf::Keyboard::Num9,

            Escape = sf::Keyboard::Escape, LControl = sf::Keyboard::LControl,
            LShift = sf::Keyboard::LShift, LAlt = sf::Keyboard::LAlt,
            LSystem = sf::Keyboard::LSystem, RControl = sf::Keyboard::RControl,
            RShift = sf::Keyboard::RShift, RAlt = sf::Keyboard::RAlt,
            RSystem = sf::Keyboard::RSystem, Menu = sf::Keyboard::Menu,

            LBracket = sf::Keyboard::LBracket, RBracket = sf::Keyboard::RBracket,
            Semicolon = sf::Keyboard::Semicolon, Comma = sf::Keyboard::Comma,
            Period = sf::Keyboard::Period, Quote = sf::Keyboard::Quote,
            Slash = sf::Keyboard::Slash, Backslash = sf::Keyboard::Backslash,
            Tilde = sf::Keyboard::Tilde, Equal = sf::Keyboard::Equal,
            Hyphen = sf::Keyboard::Hyphen, Space = sf::Keyboard::Space,
            Enter = sf::Keyboard::Enter, Backspace = sf::Keyboard::Backspace,
            Tab = sf::Keyboard::Tab, PageUp = sf::Keyboard::PageUp,
            PageDown = sf::Keyboard::PageDown, End = sf::Keyboard::End,
            Home = sf::Keyboard::Home, Insert = sf::Keyboard::Insert,
            Delete = sf::Keyboard::Delete, Add = sf::Keyboard::Add,
            Subtract = sf::Keyboard::Subtract, Multiply = sf::Keyboard::Multiply,
            Divide = sf::Keyboard::Divide,

            Left = sf::Keyboard::Left, Right = sf::Keyboard::Right,
            Up = sf::Keyboard::Up, Down = sf::Keyboard::Down,

            Numpad0 = sf::Keyboard::Numpad0, Numpad1 = sf::Keyboard::Numpad1,
            Numpad2 = sf::Keyboard::Numpad2, Numpad3 = sf::Keyboard::Numpad3,
            Numpad4 = sf::Keyboard::Numpad4, Numpad5 = sf::Keyboard::Numpad5,
            Numpad6 = sf::Keyboard::Numpad6, Numpad7 = sf::Keyboard::Numpad7,
            Numpad8 = sf::Keyboard::Numpad8, Numpad9 = sf::Keyboard::Numpad9,

            F1 = sf::Keyboard::F1, F2 = sf::Keyboard::F2, F3 = sf::Keyboard::F3,
            F4 = sf::Keyboard::F4, F5 = sf::Keyboard::F5, F6 = sf::Keyboard::F6,
            F7 = sf::Keyboard::F7, F8 = sf::Keyboard::F8, F9 = sf::Keyboard::F9,
            F10 = sf::Keyboard::F10, F11 = sf::Keyboard::F11, F12 = sf::Keyboard::F12,
            F13 = sf::Keyboard::F13, F14 = sf::Keyboard::F14, F15 = sf::Keyboard::F15,

            Pause = sf::Keyboard::Pause
        };

        ///
        /// \brief Method returns true if the key passed as an argument is pressed.
        /// \param key Button number from the Keyboard::Key enum.
        /// \return bool
        ///

        static bool isPressed(Key key); //Checks if the key is pressed.
    };

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

