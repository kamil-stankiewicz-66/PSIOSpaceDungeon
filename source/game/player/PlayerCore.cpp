#include "game/player/PlayerCore.h"
#include "engine/core/Engine.h"
#include "game/core/Asset.h"

void PlayerCore::onAwake()
{
    //tag
    this->addTag("Player");

    //player body
    this->playerBody = this->getGame()->get_currentScene()->createObject<PlayerBody>(this->getRenderLayer());
    this->addChild(this->playerBody);

    //player movement
    this->playerMove = this->getGame()->get_currentScene()->createObject<PlayerMove>();
    this->addChild(this->playerMove);
}


void PlayerBody::onAwake()
{
    this->getSpritePtr()->setTexture(Asset::Graphics::PLAYER_SKIN_02.data());
}
