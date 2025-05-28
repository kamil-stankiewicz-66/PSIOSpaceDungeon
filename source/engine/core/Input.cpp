#include "engine/core/Input.h"

sf::RenderWindow* Input::window = nullptr; //wskaznik na główne okno SFML ktorey jest potrzebny do odczytu pozycji kursora


Vector2 Input::Mouse::pos; // przechowuje biezace pozycje  kursora wzgledem srodka okna



void Input::init(sf::RenderWindow* win) { // ustawienie wskaznika na aktualne okno

    window = win;
}

void Input::update() {

    Input::Mouse::update();
}

bool Input::Keyboard::isPressed(Input::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);//sprawdza czy dany klawisz jest wcisniety
}

void Input::Mouse::update() {

    if (window) {

        auto pixel = sf::Mouse::getPosition(*window); //pobiera pozycje okna wzgledem okna
        auto size = window->getSize();
        pos.x = pixel.x - size.x / 2.f;
        pos.y = -(pixel.y - size.y / 2.f); //obliczenie pozycji wzgledem srodka okna

    }
}

const Vector2& Input::Mouse::AXIS() {

    return pos;
}

bool Input::Mouse::LEFT_BUTTON() {

    return sf::Mouse::isButtonPressed(sf::Mouse::Left); //czy lewy przycisk wcisniety
}

bool Input::Mouse::RIGHT_BUTTON() {

    return sf::Mouse::isButtonPressed(sf::Mouse::Right); //czy prawy przycisk wcisniety
}
