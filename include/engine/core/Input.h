#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>
#include "engine\core\Vector2.h"

///
/// \brief Klasa obslugujaca dane wejsciowe z klawiatury i myszy.
///

class Input
{
friend class Engine;

private:
    static sf::RenderWindow* window; //wskaznik na okno SFML,  do pobierania pozycji myszy

    static void init(sf::RenderWindow* win);  //Ta metoda jest wywolywana przez silnik.
    static void update(); //aktualizacja danych wejsciowych - Ta metoda jest wywolywana przez silnik.

public:

    ///
    /// \brief Klasa obslugujaca dane wejsciowe z klawiatury.
    ///

    class Keyboard
    {

    public:

        ///
        /// \brief Enum przechowujacy numery wybranych przyciskow klawiatury, zgodne z SFML.
        ///

        enum Key {
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
        /// \brief Metoda zwraca true, gdy przycisk podany w argumencie jest wcisniety.
        /// \param key Numer przycisku pochodzacy z enum Keyboard::Key.
        /// \return bool
        ///

        static bool isPressed(Key key); //sprawdza czy klawisz wcisniety
    };

    ///
    /// \brief Klasa obslugujaca dane wejsciowe myszy.
    ///

    class Mouse
    {
    friend class Input;

    private:

        static Vector2 pos; //pozycja myszy wzgledem srodek okna

        static void update(); //aktualizacja pozycji myszy

    public:

        ///
        /// \brief Metoda zwraca aktualna pozycje kursora w oknie.
        /// \details Kiedy kursor jest w srodku okna jego pozycja wynosi (0, 0).
        ///

        static const Vector2& AXIS();

        ///
        /// \brief Metoda zwraca true jesli lewy przycisk myszy zostal wcisniety.
        /// \return bool
        ///

        static bool LEFT_BUTTON();

        ///
        /// \brief Metoda zwraca true jesli prawy przycisk myszy zostal wcisniety.
        /// \return bool
        ///

        static bool RIGHT_BUTTON();
    };

};


#endif // INPUT_H

