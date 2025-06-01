#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine/component/Component.h"
#include "engine/core/Vector2.h"

///
/// \brief Component przechowujacy pozycje, skale i rotacje obiektu.
/// \details Obiekty ze standardowym transformem sa renderowane relatywnie do kamery.
/// Wszystkie GameObject posiadaja domyslnie ten Transform.
///

class Transform : public Component
{
private:
    bool m_rect;
    bool m_inMove;

    void onUpdate(float deltaTime) override;

protected:
    Vector2 position;
    Vector2 pre_position;
    Vector2 scale;
    float rotation;
    bool flip_x;

    void makeRect();

public:
    Transform(const Vector2& position = Vector2(),
              const Vector2& scale = Vector2(1.0f, 1.0f),
              const float& rotation = 0.0,
              const bool flipX = false
              );
    virtual ~Transform();

    //Metoda ta ustawia rzeczywista pozycje na biezaca pozycje pozorna zdefiniowana przez obiekty nadrzedne.
    void updateGlobalTransform();

    //Metoda ustawia pozycje na Vector(0, 0).
    void resetPosition();

    //Metody te modyfikuja skale, mnozac ja przez wartosc podana w argumencie.
    void scaleBy(const Vector2&);
    void scaleBy(const float&);

    //setters
    void set_position(const Vector2&);
    void add_position(const Vector2&);
    void set_rotation(const float&);
    void add_rotation(const float&);
    void set_flip_x(const bool);

    //getters
    const Vector2 get_position() const;
    const Vector2& get_prePosition() const;
    const Vector2& get_scale() const;
    const float& get_rotation() const;
    const bool get_flipX() const;

    //info
    const bool isRect() const;
    const float get_speed() const;
    const bool inMove() const;
};

///
/// \brief Component przechowujacy pozycje, skale i rotacje obiektu.
/// \details Obiekty z tym transformem sa renderowane bez wzgledu na pozycje i sizeView kamery.
/// Przeznaczone dla elementow interfejsu. Kazdy UIObject posiada domyslnie ten Transform.
///

class RectTransform : public Transform
{
public:
    RectTransform(const Vector2& position = Vector2(),
                  const Vector2& scale = Vector2(1.0f, 1.0f),
                  const double& rotation = 0.0,
                  const bool flipX = false
                  );
};

#endif // TRANSFORM_H
