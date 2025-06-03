#ifndef VMATH_H
#define VMATH_H

#include "engine/core/Vector2.h"
struct Vector2;
struct Edges;

///
/// \brief Class that contains various mathematical functions.
///

class VMath
{
public:

    //This method clamps the value to ensure it stays between the specified minimum and maximum.
    template <typename T>
    static constexpr const T& clamp(const T& value, const T& low, const T& high) {
        return (value < low) ? low : (high < value) ? high : value;
    }

    //This method checks if the value is between the minimum and maximum values.
    template <typename T>
    static constexpr const bool isInRange(const T& value, const T& min, const T& max) {
        return (min <= value) && (value <= max);
    }

    //Checks if vectors have the same direction.
    static const bool sameDirection(const Vector2& a, const Vector2& b);
};

#endif // VMATH_H
