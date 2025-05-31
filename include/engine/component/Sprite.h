#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "engine/component/Component.h"

using namespace std;
using Uint8 = unsigned char;

class Scene;
class Engine;
class VSprite;
struct Vector2;

///
/// \brief Component reprezentujący sprite.
///

class VSprite : public Component
{
    friend class Scene;

private:
    unique_ptr<sf::Texture> m_texture;
    string m_spriteRef;
    sf::Sprite m_sprite;
    unsigned short renderLayer;

    bool init(Engine* engine, Object* parent) override; //Ta metoda jest wywolywana przez silnik.
    void onLateUpdate(float) override;
    void render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect);

public:
    VSprite();

    void setTexture(const string& spriteRef);
    void setColor(const sf::Color&);
    void dispose();

    const bool isInited() const;

    //getter
    unsigned short getRenderLayer() const;
};


#endif // SPRITE_H
