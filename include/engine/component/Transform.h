#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "engine/component/Component.h"
#include "engine/core/Vector2.h"

///
/// \brief Component storing position, scale, and rotation of an object.
/// \details Objects with the standard transform are rendered relative to the camera.
/// All GameObjects have this Transform by default.
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

    //This method sets the real position to the current virtual position defined by parent objects.
    void updateGlobalTransform();

    //Method sets the position to Vector(0, 0).
    void resetPosition();

    //These methods modify the scale by multiplying it by the value given in the argument.
    void scaleBy(const Vector2&);
    void scaleBy(const float&);

    //setters
    void set_position(const Vector2&);
    void set_position(const float& x, const float& y);
    void add_position(const Vector2&);
    void add_position(const float& x, const float& y);
    void set_scale(const Vector2&);
    void set_rotation(const float&);
    void add_rotation(const float&);
    void set_flip_x(const bool);

    //getters
    const Vector2 get_position() const;
    const Vector2 get_localPosition() const;
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
/// \brief Component storing position, scale, and rotation of an object.
/// \details Objects with this transform are rendered regardless of the camera’s position and sizeView.
/// Designed for interface elements. All UIObjects have this Transform by default.
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
