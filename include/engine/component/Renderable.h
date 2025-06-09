#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "engine/component/Component.h"

using namespace std;
using Uint8 = unsigned char;
using uint = unsigned int;

class Scene;
class Engine;
struct Vector2;



///
/// \brief This component can render itself in a window.
///

class VRenderable : public Component
{
    bool m_renderWithLocalFlip = false;

protected:
    string m_assetRef;

    //engine methods
    bool init(Engine* engine, Object* parent) override; //This method is called by the engine.
    void onUpdate(float) override; //This method is called by the engine.

    ///
    /// \brief Calculates common data required for rendering.
    /// \details Used in render() method.
    ///

    void generateMatrix(const Engine* game, sf::Transform& transform, const int& width, const int& height,
                        const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect);

public:
    //abstract methods
    virtual void render(const Engine* game, const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) = 0;
    const virtual bool isInited() const = 0;

    //virtual methods
    virtual void dispose();

    //render with local or parent dependent reflection
    void setRenderWithLocalFlip(const bool);

    //getter
    const string_view getAssetRef() const;
};



///
/// \brief A component that represents a sprite.
///

class VSprite : public VRenderable
{

private:
    sf::Sprite m_sprite;
    shared_ptr<sf::Texture> m_texture;

public:
    virtual void render(const Engine* game, const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) override;
    virtual const bool isInited() const override;

    virtual void dispose() override;

    //sprite api
    void setTexture(const string& asset_ref);
    void setTexture(shared_ptr<sf::Texture>&);
    void setColor(const sf::Color&);
    void setTextureRect(const sf::IntRect&);
    const sf::IntRect& getTextureRect() const;
};



///
/// \brief A component that represents a text.
///

class VText : public VRenderable
{

private:
    sf::Text m_text;
    unique_ptr<sf::Font> m_font;

public:
    virtual void render(const Engine* game, const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect) override;
    virtual const bool isInited() const override;

    virtual void dispose() override;

    //text api setters
    void setText(const string& text);
    void setFont(const string& asser_ref);
    void setStyle(const sf::Text::Style&);
    void setCharacterSize(const Uint8&);
    void setLetterSpacing(const float&);
    void setLineSpacing(const float&);
    void setFillColor(const sf::Color&);
    void setOutlineColor(const sf::Color&);
    void setOutlineThickness(const float&);

    //text api getters
    const string getText() const;
    const sf::FloatRect getLocalBounds() const;
};

#endif // RENDERABLE_H
