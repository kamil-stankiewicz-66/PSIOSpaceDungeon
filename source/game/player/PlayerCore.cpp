#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"

///
/// PlayerCore
///

void PlayerCore::onAwake()
{
    //tag
    this->addTag("Player");


    //ptr
    Scene* _scenePtr = this->getGame()->get_currentScene();


    //creating player body
    playerBody = _scenePtr->createObject<GameObject>(getRenderLayer());
    playerBody->addTag("PlayerBody");
    this->addChild(playerBody);
    playerBody->getSpritePtr()->setTexture(m_bodyTexture);
    playerBody->getSpritePtr()->setTextureRect(sf::IntRect(49, 3, 41, 59));

    playerLegLeft = _scenePtr->createObject<GameObject>(getRenderLayer()-1);
    playerLegLeft->addTag("PlayerLegLeft");
    this->addChild(playerLegLeft);
    playerLegLeft->getSpritePtr()->setTexture(m_bodyTexture);
    playerLegLeft->getSpritePtr()->setTextureRect(sf::IntRect(53, 67, 11, 7));
    playerLegLeft->getTransformPtr()->set_position(-23.f, -65.f);

    playerLegRight = _scenePtr->createObject<GameObject>(getRenderLayer()-1);
    playerLegRight->addTag("PlayerLegRight");
    this->addChild(playerLegRight);
    playerLegRight->getSpritePtr()->setTexture(m_bodyTexture);
    playerLegRight->getSpritePtr()->setTextureRect(sf::IntRect(68, 67, 11, 7));
    playerLegRight->getTransformPtr()->set_position(10.f, -65.f);

    playerCape = _scenePtr->createObject<GameObject>(getRenderLayer()+1);
    playerCape->addTag("PlayerCape");
    playerBody->addChild(playerCape);
    playerCape->getSpritePtr()->setTexture(m_bodyTexture);
    playerCape->getSpritePtr()->setTextureRect(sf::IntRect(24, 35, 19, 28));
    playerCape->getTransformPtr()->set_position(-30.f, -35.f);


    //player movement
    playerMove = _scenePtr->createObject<PlayerMove>();
    playerMove->addTag("Script_PlayerMove");
    this->addChild(this->playerMove);

    //player animations
    playerAnim = _scenePtr->createObject<PlayerAnim>();
    playerAnim->addTag("Script_PlayerAnim");
    this->addChild(this->playerAnim);
}

