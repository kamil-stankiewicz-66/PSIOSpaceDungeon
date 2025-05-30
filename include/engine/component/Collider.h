#ifndef COLLIDER_H
#define COLLIDER_H

#include "engine/component/Component.h"
#include <set>

struct Vector2;
class Transform;
class CollisionManager;

///
/// \brief Struktura przechowujaca punkty krancowe Collidera.
///

struct Edges
{
    int x_min, x_max;
    int y_min, y_max;
    Edges(int x_min = 0, int x_max = 0, int y_min = 0, int y_max = 0);
};

///
/// \brief Klasa bazowa Collidera. Kazdy Collider musi byc rodzajem tej klasy.
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
    /// \brief Metoda sprawdza czy ten Collider jest w kolizji z Colliderem podanym w argumencie.
    /// \param other_collider Collider obiektu, z ktorym wykrywana jest kolizja.
    /// \param other_transform Transform obiektu, z ktorym wykrywana jest kolizja.
    /// \return bool
    ///

    virtual bool checkCollision(Collider* other_collider, Transform* other_transform) = 0; //Ta metoda jest wywolywana przez silnik.

public:
    Collider();
    virtual ~Collider();
    void refreshCollisions();


    ///
    /// \brief Metoda sprawdza czy punkt nalezy do Collidera.
    /// \param point Pozycja punktu.
    /// \return bool
    ///

    virtual bool isThisPointInCollider(const Vector2& point) = 0;


    ///
    /// \brief Metoda znajduje punkt nalezacy do Collidera, ktory jest najblizej punktu podanego w argumencie.
    /// \param point Pozycja punktu.
    /// \param borderThickness Wirtualna granica Collidera (ramka).
    /// \return Vector2
    ///

    virtual Vector2 getNearestColliderPointTo(const Vector2& point, const float borderThickness = 0.0f) = 0;


    ///
    /// \brief Metoda zwraca punkty krancowe Collidera.
    /// \return Edges
    ///

    virtual Edges getEdges() const = 0;


    ///
    /// \brief Uniwersalna metoda sprawdzajaca czy ten Collider jest w kolizji z Colliderem podanym w argumencie.
    /// \details Wykrywanie kolizji pomiedzy Colliderami roznych typow jest dozwolone.
    /// \param collider Inny Collider.
    /// \return bool
    ///

    bool isInCollisionWith(Collider* collider);


    //Metoda zwraca kolekcje ze wszystkimi Colliderami, z ktorymi jest w kolizji ten Collider.
    const std::set<Collider*>& getCollisions() const;
};

///
/// \brief Collider o ksztalcie prostokata
///

class BoxCollider : public Collider
{
private:
    float x = 0.0f;
    float y = 0.0f;

    float leftEdge, rightEdge, downEdge, upEdge;

    void onUpdate(float) override; //Ta metoda jest wywolywana przez silnik.
    bool checkCollision(Collider* other_collider, Transform* other_transform) override; //Ta metoda jest wywolywana przez silnik.

    //helper
    void updateEdges(); //Ta metoda jest wywolywana przez silnik.

public:
    //Metoda ustawiajaca rozmiar Collidera.
    void set(float size_x, float size_y);

    //Definicje metod abstrakcyjnych
    bool isThisPointInCollider(const Vector2&) override;
    Vector2 getNearestColliderPointTo(const Vector2&, const float borderThickness = 0.0f) override;
    Edges getEdges() const override;

    //getters
    const float& getSize_x() const;
    const float& getSize_y() const;
};

#endif // COLLIDER_H
