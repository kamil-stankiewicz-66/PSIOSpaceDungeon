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


void VRenderable::generateMatrix(sf::Transform& sftransform, const int& width, const int& height,
                                 const Vector2& position, const Vector2& scale, const float& rotationZ, const bool flipX, const bool isRect)
{
    float screen_zeroX = static_cast<float>(getGame()->get_window()->get_displaymode().width) / 2.0f;
    float screen_zeroY = static_cast<float>(getGame()->get_window()->get_displaymode().height) / 2.0f;

    float r_posX = screen_zeroX;
    float r_posY = screen_zeroY;

    float sfTxtSizeX = static_cast<float>(width);
    float sfTxtSizeY = static_cast<float>(height);

    float r_sizeX = sfTxtSizeX * scale.x;
    float r_sizeY = sfTxtSizeY * scale.y;


    //relative to the camera
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


    //mirror
    int r_flipX = flipX ? -1.f : 1.f;


    //camera rotation
    if (!isRect && _camera) {
        sftransform.translate(screen_zeroX, screen_zeroY);
        sftransform.rotate(-_camera->transform->get_rotation());
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

    //transform
    sf::Transform transform;
    this->generateMatrix(transform, m_sprite.getTextureRect().width, m_sprite.getTextureRect().height,
                         position, scale, rotationZ, flipX, isRect);

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
