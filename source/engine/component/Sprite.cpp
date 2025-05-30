#include "engine/component/Sprite.h"
#include "engine/core/Scene.h"
#include "engine/core/Engine.h"
#include "engine/object/Camera.h"


//sprite

VSprite::VSprite() : renderLayer(0)
{}

bool VSprite::init(Engine* game, Object* parent)
{
    if (Component::init(game, parent))
    {
        return true;
    }

    return false;
}


void VSprite::render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    if (!this->isInited()) {
        return;
    }

    float sfTxtSizeX = static_cast<float>(this->m_sprite.getTexture()->getSize().x);
    float sfTxtSizeY = static_cast<float>(this->m_sprite.getTexture()->getSize().y);

    float screen_zeroX = static_cast<float>(getGame()->get_window()->get_displaymode().width) / 2.0f;
    float screen_zeroY = static_cast<float>(getGame()->get_window()->get_displaymode().height) / 2.0f;

    float r_sizeX = sfTxtSizeX * scale.x;
    float r_sizeY = sfTxtSizeY * scale.y;

    float r_posX = screen_zeroX;
    float r_posY = screen_zeroY;


    //uwzglednienie kamery
    const Camera* _camera = this->getObject()->getGame()->get_currentScene()->get_mainCamera();
    if (!isRect && _camera)
    {
        r_sizeX /= _camera->get_viewSize();
        r_sizeY /= _camera->get_viewSize();

        r_posX -= ((r_sizeX / 2.0f) - ((position.x - _camera->transform->get_position().x) / _camera->get_viewSize()));
        r_posY -= ((r_sizeY / 2.0f) + ((position.y - _camera->transform->get_position().y) / _camera->get_viewSize()));
    }
    else
    {
        r_posX -= ((r_sizeX / 2.0f) - position.x);
        r_posY -= ((r_sizeY / 2.0f) + position.y);
    }


    //odbicie lustrzane
    int r_flipX = flipX ? -1.f : 1.f;


    //rotacja bezwgledna
    m_sprite.setOrigin(m_sprite.getTextureRect().width *0.5f, m_sprite.getTextureRect().height *0.5f);
    m_sprite.setRotation(rotationZ);

    //uwzglednie rotacji kamery
    sf::Transform transform;
    if (!isRect && _camera)
    {
        transform.translate(screen_zeroX, screen_zeroY);
        transform.rotate(-_camera->get_rotation());
        transform.translate(-screen_zeroX, -screen_zeroY);
    }

    //translacja
    m_sprite.setPosition(r_posX, r_posY);

    //skalowanie
    m_sprite.setScale(r_sizeX * r_flipX, r_sizeY);


    //draw
    getGame()->get_window()->get_renderwindow()->draw(m_sprite, transform);
}


//setter

void VSprite::setTexture(const string& sprite_ref)
{
    if (this->m_spriteRef == sprite_ref) {
        return;
    }

    if (!m_texture) {
        m_texture = make_unique<sf::Texture>();
    }

    if (!m_texture->loadFromFile(sprite_ref)) {
        VDebuger::print("SPRITE :: TEXTURE :: ERROR - downloading sprite:", sprite_ref);
    }

    this->m_sprite.setTexture(*m_texture);
    this->m_spriteRef = sprite_ref;
}

void VSprite::setColor(const sf::Color& _c)
{
    this->m_sprite.setColor(_c);
}

void VSprite::dispose()
{
    this->m_texture = nullptr;
    this->m_sprite = sf::Sprite();
    this->m_spriteRef.clear();
}


const bool VSprite::isInited() const
{
    return this->m_texture.get();
}


//getter

unsigned short VSprite::getRenderLayer() const
{
    return this->renderLayer;
}
