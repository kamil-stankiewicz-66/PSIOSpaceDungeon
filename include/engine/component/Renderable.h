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
/// \brief Component renderujacy sie w oknie.
///

class VRenderable : public Component
{

protected:
    string m_assetRef;

    //engine methods
    bool init(Engine* engine, Object* parent) override; //Ta metoda jest wywolywana przez silnik.
    void onLateUpdate(float) override;

    ///
    /// \brief Calculates common data required for rendering.
    /// \details Used in render() method.
    ///

    void calculateRenderData(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect,
                             float& screen_zeroX, float& screen_zeroY, float& r_posX, float& r_posY, float& r_sizeX, float& r_sizeY);

public:
    //abstract methods
    virtual void render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) = 0;
    const virtual bool isInited() const = 0;

    //virtual methods
    virtual void dispose();
};



///
/// \brief Component reprezentujący sprite.
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
