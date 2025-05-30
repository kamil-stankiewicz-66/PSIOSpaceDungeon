#ifndef VMATH_H
#define VMATH_H

struct Vector2;
struct Edges;

///
/// \brief Klasa przechowujaca rozne funkcje matematyczne.
///

class VMath
{
public:

    //Ta metoda ogranicza wartosc, aby miec pewnosc, ze miesci sie ona pomiedzy okreslonym minimum i maksimum.
    template <typename T>
    static constexpr const T& clamp(const T& value, const T& low, const T& high) {
        return (value < low) ? low : (high < value) ? high : value;
    }

    //Ta metoda sprawdza, czy wartosc miesci sie pomiedzy wartoscia minimalna i maksymalna.
    template <typename T>
    static constexpr const bool isInRange(const T& value, const T& min, const T& max) {
        return (min <= value) && (value <= max);
    }
};

#endif // VMATH_H
