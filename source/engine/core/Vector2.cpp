#include "engine/core/Vector2.h"

#include <cmath>


///
/// operators
///

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator+(const float& other) const {
    return Vector2(this->x + other, this->y + other);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator-(const float& other) const {
    return Vector2(this->x - other, this->y - other);
}

Vector2 Vector2::operator*(const Vector2& other) const {
    return Vector2(this->x * other.x, this->y * other.y);
}

Vector2 Vector2::operator*(const float& other) const {
    return Vector2(this->x * other, this->y * other);
}

Vector2 Vector2::operator/(const Vector2& other) const {
    return Vector2(this->x / other.x, this->y / other.y);
}

Vector2 Vector2::operator/(const float& other) const {
    return Vector2(this->x / other, this->y / other);
}

bool Vector2::operator==(const Vector2& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const {
    return (this->x != other.x) || (this->y != other.y);
}

bool Vector2::operator<(const Vector2& other) const {
    return this->moduloLite() < other.moduloLite();
}

bool Vector2::operator>(const Vector2& other) const {
    return this->moduloLite() > other.moduloLite();
}


///
/// methods
///

Vector2::Vector2(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

void Vector2::clear()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

void Vector2::normalize()
{
    float _mod = this->modulo();

    if (_mod == 0.0f || _mod == 1.0f) {
        return;
    }

    x = x / (_mod);
    y = y / (_mod);
}

Vector2 Vector2::get_normalized() const
{
    float _mod = this->modulo();

    if (_mod == 0)
    {
        return Vector2();
    }

    return Vector2(
        x / (_mod),
        y / (_mod)
        );
}

float Vector2::distanceToLite(const Vector2& arg_vec) const
{
    float dx = arg_vec.x - this->x;
    float dy = arg_vec.y - this->y;

    float dxp = dx * dx;
    float dyp = dy * dy;

    return dxp + dyp;
}

float Vector2::distanceTo(const Vector2& arg_vec) const
{
    return std::sqrt(this->distanceToLite(arg_vec));
}

float Vector2::moduloLite() const
{
    return (this->x * this->x) + (this->y * this->y);
}

float Vector2::modulo() const
{
    return std::sqrt(this->moduloLite());
}
