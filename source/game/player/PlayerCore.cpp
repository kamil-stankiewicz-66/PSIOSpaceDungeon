#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"
#include "game/entity/Weapon.h"

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
    playerLegLeft->getSpritePtr()->setTextureRect(sf::IntRect(53, 63, 11, 11));
    playerLegLeft->getTransformPtr()->set_position(-23.f, -63.f);

    playerLegRight = _scenePtr->createObject<GameObject>(getRenderLayer()-1);
    playerLegRight->addTag("PlayerLegRight");
    this->addChild(playerLegRight);
    playerLegRight->getSpritePtr()->setTexture(m_bodyTexture);
    playerLegRight->getSpritePtr()->setTextureRect(sf::IntRect(68, 63, 11, 11));
    playerLegRight->getTransformPtr()->set_position(10.f, -63.f);

    playerCape = _scenePtr->createObject<GameObject>(getRenderLayer()+1);
    playerCape->addTag("PlayerCape");
    playerBody->addChild(playerCape);
    playerCape->getSpritePtr()->setTexture(m_bodyTexture);
    playerCape->getSpritePtr()->setTextureRect(sf::IntRect(24, 35, 19, 28));
    playerCape->getTransformPtr()->set_position(-30.f, -35.f);


    //weapon
    weapon = _scenePtr->createObject<AssaultRifle>(getRenderLayer() + 2);
    weapon->getSpritePtr()->setTexture(Asset::Graphics::ASSAULT_RIFLE_01.data());
    playerBody->addChild(weapon);
    weapon->getTransformPtr()->add_position(10.0f, -20.0f);



    //collider
    collider = createComponent<CircleCollider>();
    collider->set(80.0f);
    rb = createComponent<Rigidbody>();


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

