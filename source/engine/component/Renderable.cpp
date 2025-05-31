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


void VRenderable::onLateUpdate(float)
{
    if (auto _t = getObject()->transform)
    {
        this->render(_t->get_position(),
                     _t->get_scale(),
                     _t->get_rotation(),
                     _t->get_flipX(),
                     _t->isRect());
    }
}


void VRenderable::calculateRenderData(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect,
                                      float& screen_zeroX, float& screen_zeroY, float& r_posX, float& r_posY, float& r_sizeX, float& r_sizeY)
{
    screen_zeroX = static_cast<float>(getGame()->get_window()->get_displaymode().width) / 2.0f;
    screen_zeroY = static_cast<float>(getGame()->get_window()->get_displaymode().height) / 2.0f;

    r_posX = screen_zeroX;
    r_posY = screen_zeroY;


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
}


void VRenderable::dispose()
{
    m_assetRef.clear();
}



///
/// Sprite
///


void VSprite::render(const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    if (!this->isInited()) {
        return;
    }

    float screen_zeroX = 0.0f;
    float screen_zeroY = 0.0f;
    float r_posX = 0.0f;
    float r_posY = 0.0f;
    float r_sizeX = 0.0f;
    float r_sizeY = 0.0f;


    this->calculateRenderData(position, scale, rotationZ, flipX, isRect,
                              screen_zeroX, screen_zeroY, r_posX, r_posY, r_sizeX, r_sizeY);


    float sfTxtSizeX = static_cast<float>(this->m_sprite.getTexture()->getSize().x);
    float sfTxtSizeY = static_cast<float>(this->m_sprite.getTexture()->getSize().y);

    r_sizeX = sfTxtSizeX * scale.x;
    r_sizeY = sfTxtSizeY * scale.y;

    //odbicie lustrzane
    int r_flipX = flipX ? -1.f : 1.f;


    //rotacja bezwgledna
    m_sprite.setOrigin(m_sprite.getTextureRect().width *0.5f, m_sprite.getTextureRect().height *0.5f);
    m_sprite.setRotation(rotationZ);

    //uwzglednie rotacji kamery
    Camera* _camera = getGame()->get_currentScene()->get_mainCamera();
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


const bool VSprite::isInited() const
{
    return m_texture.get();
}


void VSprite::dispose()
{
    VRenderable::dispose();
    m_sprite = sf::Sprite();
    m_texture = nullptr;
}


void VSprite::setTexture(const string& asset_ref)
{
    if (this->m_assetRef == asset_ref) {
        return;
    }

    if (!m_texture) {
        m_texture = make_unique<sf::Texture>();
    }

    if (!m_texture->loadFromFile(asset_ref)) {
        VDebuger::print("SPRITE :: TEXTURE :: ERROR - downloading sprite:", asset_ref);
    }

    this->m_sprite.setTexture(*m_texture);
    this->m_assetRef = asset_ref;
}

void VSprite::setColor(const sf::Color& _c)
{
    this->m_sprite.setColor(_c);
}
