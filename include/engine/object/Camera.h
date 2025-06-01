#ifndef CAMERA_H
#define CAMERA_H

#include "engine/object/Object.h"
#include <cfloat>

///
/// \brief Klasa reprezentujaca podstawowa kamere.
///

class Camera : public GameObject
{
private:
    static constexpr float MIN_VIEWSIZE = FLT_MIN;

    ///
    /// \brief Parametr okreslajacy zakres widocznosci.
    /// \details Okresla rozmiar obszaru, ktory kamera jest w stanie zobaczyc w danym momencie.
    /// Definiuje, jak duza czesc swiata gry bedzie wyswietlana na ekranie.
    ///

    float view_size;

public:
    Camera();

    //setters
    void set_viewSize(const float&);

    //getters
    const float& get_viewSize() const;
};

#endif // CAMERA_H
