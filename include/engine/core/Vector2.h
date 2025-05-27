#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

///
/// \brief Struktura definiujaca wektor o dwoch skladowych: x i y.
///

struct Vector2
{
    //operators
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator+(const float& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator-(const float& other) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator*(const float& other) const;
    Vector2 operator/(const Vector2& other) const;
    Vector2 operator/(const float& other) const;
    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
    bool operator<(const Vector2& other) const;
    bool operator>(const Vector2& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }


    float x, y;
    Vector2(float x = 0.0f, float y = 0.0f);


    //Metoda ustawia wartosc x i y na 0;
    void clear();

    //Ta metoda zwraca ten wektor w wersji znormalizowanej.
    Vector2 get_normalized() const;

    //Te metody zwracaja odleglosc do wektora podanego w argumencie...
    float distanceToLite(const Vector2&) const; //bez pierwiastkowania.
    float distanceTo(const Vector2&) const; //rzeczywista odleglosc.

    //Ta metoda zwraca dlugosc tego wektora...
    float moduloLite() const; //bez pierwiastkowania.
    float modulo() const; //rzeczywista dlugosc.
};

#endif // VECTOR2_H
