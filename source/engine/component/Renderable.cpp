#include "engine/component/Renderable.h"
#include "engine/core/Scene.h"
#include "engine/core/Engine.h"
#include "engine/object/Camera.h"



///
/// Renderable
///


bool VRenderable::init(Engine* game, Object* parent)
{
    if (Component::init(game, parent))
    {
        return true;
    }

    return false;
}


void VRenderable::onUpdate(float)
{
    if (!getGame()) {
        return;
    }

    if (auto _t = getObject()->getTransformPtr())
    {
        this->render(getGame(),
                     _t->get_position(),
                     _t->get_scale(),
                     _t->get_rotation(),
                     m_renderWithLocalFlip ? _t->get_localFlipX() : _t->get_flipX(),
                     _t->isRect());
    }
}


void VRenderable::generateMatrix(const Engine* game, sf::Transform& sftransform, const int& width, const int& height,
                                 const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    if (!game || !game->get_window()) {
        return;
    }

    float screen_zeroX = static_cast<float>(game->get_window()->get_displaymode().width) / 2.0f;
    float screen_zeroY = static_cast<float>(game->get_window()->get_displaymode().height) / 2.0f;

    float r_posX = screen_zeroX;
    float r_posY = screen_zeroY;

    float r_sizeX = scale.x;
    float r_sizeY = scale.y;


    //relative to the camera
    Camera* _camera = game->get_currentScene()->get_mainCamera();
    if (!isRect && _camera && _camera->getTransformPtr())
    {
        r_sizeX /= _camera->get_viewSize();
        r_sizeY /= _camera->get_viewSize();

        r_posX -= ((r_sizeX / 2.0f) - ((position.x - _camera->getTransformPtr()->get_position().x) / _camera->get_viewSize()));
        r_posY -= ((r_sizeY / 2.0f) + ((position.y - _camera->getTransformPtr()->get_position().y) / _camera->get_viewSize()));
    }
    else
    {
        r_posX -= ((r_sizeX / 2.0f) - position.x);
        r_posY -= ((r_sizeY / 2.0f) + position.y);
    }


    //mirror
    int r_flipX = flipX ? -1.f : 1.f;


    //camera rotation
    if (!isRect && _camera) {
        sftransform.translate(screen_zeroX, screen_zeroY);
        sftransform.rotate(-_camera->getTransformPtr()->get_rotation());
        sftransform.translate(-screen_zeroX, -screen_zeroY);
    }

    //translation
    sftransform.translate(r_posX, r_posY);

    //scale
    sftransform.scale(r_sizeX * r_flipX, r_sizeY);

    //rotation
    sftransform.rotate(rotationZ);
    sftransform.translate(-width *0.5f, -height *0.5f);
}


void VRenderable::dispose()
{

}


void VRenderable::setRenderWithLocalFlip(const bool b) {
    this->m_renderWithLocalFlip = b;
}



///
/// Sprite
///


void VSprite::render(const Engine* game, const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    if (!this->isInited()) {
        return;
    }

    if (!game) {
        return;
    }

    //transform
    sf::Transform transform;
    this->generateMatrix(game, transform, m_sprite.getTextureRect().width, m_sprite.getTextureRect().height,
                         position, scale, rotationZ, flipX, isRect);

    //draw
    if (game && game->get_window() && game->get_window()->get_renderwindow())
    {
        game->get_window()->get_renderwindow()->draw(m_sprite, transform);
    }
}


const bool VSprite::isInited() const
{
    return m_texture;
}


void VSprite::dispose()
{
    VRenderable::dispose();
    m_sprite = sf::Sprite();
    m_texture = nullptr;
}

void VSprite::setTexture(sf::Texture* texture)
{
    if (!texture) {
        return;
    }

    this->dispose();

    m_texture = texture;
    m_sprite.setTexture(*m_texture);
}

void VSprite::setColor(const sf::Color& _c)
{
    this->m_sprite.setColor(_c);
}

void VSprite::setTextureRect(const sf::IntRect& rect)
{
    this->m_sprite.setTextureRect(rect);
}

const sf::IntRect& VSprite::getTextureRect() const
{
    return m_sprite.getTextureRect();
}



///
/// Text
///


void VText::render(const Engine* game, const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    if (!this->isInited()) {
        return;
    }

    if (!game) {
        return;
    }

    m_text.setOrigin(m_text.getLocalBounds().left,
                     m_text.getLocalBounds().top);

    //transform
    sf::Transform transform;
    this->generateMatrix(game, transform, m_text.getLocalBounds().width, m_text.getLocalBounds().height,
                         position, Vector2(1.f, 1.f), rotationZ, flipX, isRect);

    //draw
    if (game && game->get_window() && game->get_window()->get_renderwindow())
    {
        game->get_window()->get_renderwindow()->draw(m_text, transform);
    }
}


const bool VText::isInited() const
{
    return m_font;
}


void VText::dispose()
{
    VRenderable::dispose();
    m_text = sf::Text();
    m_font = nullptr;
}


void VText::setText(const string& text)
{
    this->m_text.setString(text);
}

void VText::setFont(sf::Font* font)
{
    if (!font) {
        return;
    }

    this->dispose();

    m_font = font;
    m_text.setFont(*m_font);
}

void VText::setStyle(const sf::Text::Style& style)
{
    this->m_text.setStyle(style);
}

void VText::setCharacterSize(const Uint8& size)
{
    this->m_text.setCharacterSize(size);
}

void VText::setLetterSpacing(const float& factor)
{
    this->m_text.setLetterSpacing(factor);
}

void VText::setLineSpacing(const float& factor)
{
    this->m_text.setLineSpacing(factor);
}

void VText::setFillColor(const sf::Color& color)
{
    this->m_text.setFillColor(color);
}

void VText::setOutlineColor(const sf::Color& color)
{
    this->m_text.setOutlineColor(color);
}

void VText::setOutlineThickness(const float& thickness)
{
    this->m_text.setOutlineThickness(thickness);
}


const string VText::getText() const
{
    return this->m_text.getString();
}

const sf::FloatRect VText::getLocalBounds() const {
    return m_text.getLocalBounds();
}
