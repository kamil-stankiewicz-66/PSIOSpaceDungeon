#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "engine/component/Component.h"

using namespace std;
using Uint8 = unsigned char;

class Scene;
class Engine;
struct Vector2;



///
/// \brief This component can render itself in a window.
///

class VRenderable : public Component
{

protected:
    string m_assetRef;

    //engine methods
    bool init(Engine* engine, Object* parent) override; //This method is called by the engine.
    void onLateUpdate(float) override; //This method is called by the engine.

    ///
    /// \brief Calculates common data required for rendering.
    /// \details Used in render() method.
    ///

    void generateMatrix(sf::Transform& transform, const int& width, const int& height,
                        const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect);

public:
    //abstract methods
    virtual void render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) = 0;
    const virtual bool isInited() const = 0;

    //virtual methods
    virtual void dispose();
};



///
/// \brief A component that represents a sprite.
///

class VSprite : public VRenderable
{

private:
    sf::Sprite m_sprite;
    unique_ptr<sf::Texture> m_texture;

public:
    virtual void render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) override;
    virtual const bool isInited() const override;

    virtual void dispose() override;

    //sprite api
    void setTexture(const string& asset_ref);
    void setColor(const sf::Color&);
};

#endif // RENDERABLE_H
