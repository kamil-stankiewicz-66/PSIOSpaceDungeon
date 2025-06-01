#ifndef COLLIDER_H
#define COLLIDER_H

#include "engine/component/Component.h"
#include <set>

struct Vector2;
class Transform;
class CollisionManager;

///
/// \brief Structure storing the edge points of a Collider
///

struct Edges
{
    int x_min, x_max;
    int y_min, y_max;
    Edges(int x_min = 0, int x_max = 0, int y_min = 0, int y_max = 0);
};

///
/// \brief Base class for a Collider. Every Collider must be derived from this class.
///

class Collider : public Component
{
    friend class Object;
    friend class CollisionManager;

private:
    static constexpr int m_chunksCheckingRange = 1;
    Edges chunks;
    std::set<Collider*> m_collisions;

protected:
    bool init(Engine*, Object*) override; //This method is called by the engine.


    ///
    /// \brief Checks if this Collider is colliding with the given Collider.
    /// \param other_collider The Collider of the object to check collision against.
    /// \param other_transform The Transform of the object to check collision against.
    /// \return bool
    ///

    virtual bool checkCollision(Collider* other_collider, Transform* other_transform) = 0; //This method is called by the engine.

public:
    Collider();
    virtual ~Collider();
    void refreshCollisions();


    ///
    /// \brief Checks if a point belongs to the Collider.
    /// \param point Position of the point.
    /// \return bool
    ///

    virtual bool isThisPointInCollider(const Vector2& point) = 0;


    ///
    /// \brief Finds the point on the Collider closest to the given point.
    /// \param point Position of the point.
    /// \param borderThickness Virtual border (margin) of the Collider.
    /// \return Vector2
    ///

    virtual Vector2 getNearestColliderPointTo(const Vector2& point, const float borderThickness = 0.0f) = 0;


    ///
    /// \brief Returns the edge points of the Collider.
    /// \return Edges
    ///

    virtual Edges getEdges() const = 0;


    ///
    /// \brief General method to check if this Collider is colliding with the given Collider.
    /// \details Collision detection between different types of Colliders is supported.
    /// \param collider Another Collider.
    /// \return bool
    ///

    bool isInCollisionWith(Collider* collider);


    ///
    /// \brief Method returns a collection of all Colliders this Collider is colliding with.
    ///

    const std::set<Collider*>& getCollisions() const;
};

///
/// \brief Collider with a rectangular shape.
///

class BoxCollider : public Collider
{
private:
    float x = 0.0f;
    float y = 0.0f;

    float leftEdge, rightEdge, downEdge, upEdge;

    void onUpdate(float) override; //This method is called by the engine.
    bool checkCollision(Collider* other_collider, Transform* other_transform) override; //This method is called by the engine.

    //helper
    void updateEdges(); //This method is called by the engine.

public:
    //Method that sets the size of the Collider.
    void set(float size_x, float size_y);

    //Definitions of abstract methods
    bool isThisPointInCollider(const Vector2&) override;
    Vector2 getNearestColliderPointTo(const Vector2&, const float borderThickness = 0.0f) override;
    Edges getEdges() const override;

    //getters
    const float& getSize_x() const;
    const float& getSize_y() const;
};

#endif // COLLIDER_H
