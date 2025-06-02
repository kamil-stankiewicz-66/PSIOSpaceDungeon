#ifndef PLAYERCORE_H
#define PLAYERCORE_H

#include "engine/object/Object.h"
#include "game/core/Asset.h"
#include "game/player/PlayerMove.h"

class PlayerBody;
class PlayerLegLeft;
class PlayerLegRight;


///
/// The PlayerCore class.
/// Main player object.
///

class PlayerCore : public GameObject
{
private:
    const string m_bodyTexture = Asset::Graphics::PLAYER_SKIN_02.data();

    //body
    GameObject* playerBody = nullptr;
    GameObject* playerLegLeft = nullptr;
    GameObject* playerLegRight = nullptr;
    GameObject* playerCape = nullptr;

    //scripts
    PlayerMove* playerMove = nullptr;

protected:
    virtual void onAwake() override;
};

#endif // PLAYERCORE_H
