#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"
#include "game/core/Tag.h"

///
/// PlayerCore
///

void PlayerCore::onStart()
{
    //tag
    this->addTag(Tag::PLAYER_CORE.data());


    //ptr
    Scene* _scenePtr = this->getGame()->get_currentScene();


    //rect
    playerRect = _scenePtr->createObject<GameObject>();
    playerRect->addTag(Tag::PLAYER_RECT.data());
    this->addChild(playerRect);
    playerRect->getTransformPtr()->add_position(0.0f, -40.0f);


    //creating player body
    playerBody = _scenePtr->createObject<GameObject>(getRenderLayer());
    playerBody->addTag(Tag::PLAYER_BODY.data());
    this->addChild(playerBody);
    playerBody->getSpritePtr()->setTexture(m_bodyTexture);
    playerBody->getSpritePtr()->setTextureRect(sf::IntRect(49, 3, 41, 59));

    playerLegLeft = _scenePtr->createObject<GameObject>(getRenderLayer()-1);
    playerLegLeft->addTag(Tag::PLAYER_LEG_LEFT.data());
    this->addChild(playerLegLeft);
    playerLegLeft->getSpritePtr()->setTexture(m_bodyTexture);
    playerLegLeft->getSpritePtr()->setTextureRect(sf::IntRect(53, 63, 11, 11));
    playerLegLeft->getTransformPtr()->set_position(-23.f, -63.f);

    playerLegRight = _scenePtr->createObject<GameObject>(getRenderLayer()-1);
    playerLegRight->addTag(Tag::PLAYER_LEG_RIGHT.data());
    this->addChild(playerLegRight);
    playerLegRight->getSpritePtr()->setTexture(m_bodyTexture);
    playerLegRight->getSpritePtr()->setTextureRect(sf::IntRect(68, 63, 11, 11));
    playerLegRight->getTransformPtr()->set_position(10.f, -63.f);

    playerCape = _scenePtr->createObject<GameObject>(getRenderLayer()+1);
    playerCape->addTag(Tag::PLAYER_CAPE.data());
    playerBody->addChild(playerCape);
    playerCape->getSpritePtr()->setTexture(m_bodyTexture);
    playerCape->getSpritePtr()->setTextureRect(sf::IntRect(24, 35, 19, 28));
    playerCape->getTransformPtr()->set_position(-30.f, -35.f);


    //hand
    hand = _scenePtr->createObject<GameObject>(getRenderLayer() + 2);
    playerBody->addChild(hand);
    hand->getTransformPtr()->add_position(10.0f, -20.0f);


    //collider
    collider = createComponent<CircleCollider>();
    collider->set(50.0f);

    //rigidbody
    rb = createComponent<Rigidbody>();
    rb->init(getTransformPtr(), playerRect->getTransformPtr());


    //player movement
    playerMove = _scenePtr->createObject<PlayerMove>();
    playerMove->addTag("Script_PlayerMove");
    this->addChild(this->playerMove);

    //player animations
    playerAnim = _scenePtr->createObject<PlayerAnim>();
    playerAnim->addTag("Script_PlayerAnim");
    this->addChild(this->playerAnim);

    //player attack
    playerAttack = _scenePtr->createObject<PlayerAttack>();
    playerAttack->addTag("Script_PlayerAttack");
    this->addChild(this->playerAttack);
}

