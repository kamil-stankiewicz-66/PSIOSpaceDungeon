#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

///
/// \brief Structure that defines a vector with two components: x and y.
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


    //Method sets x and y values to 0;
    void clear();

    //Methods normalize this vetor
    void normalize();

    //This method returns this vector in a normalized form
    Vector2 get_normalized() const;

    //These methods return the distance to the vector given as an argument...
    float distanceToLite(const Vector2&) const; //without square root.
    float distanceTo(const Vector2&) const; //actual distance.

    //This method returns the length of this vector...
    float moduloLite() const; //without square root.
    float modulo() const; //actual length.

    //Is the vector zero.
    const bool zero() const;
};

#endif // VECTOR2_H
