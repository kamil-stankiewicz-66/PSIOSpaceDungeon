#ifndef PLAYERCORE_H
#define PLAYERCORE_H

#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "game/core/Asset.h"
#include "game/physics/Rigidbody.h"
#include "game/player/PlayerAnim.h"
#include "game/player/PlayerMove.h"

///
/// The PlayerCore class.
/// Main player object.
///

class PlayerCore : public GameObject
{
    friend class PlayerMove;
    friend class PlayerAnim;

private:
    const string m_bodyTexture = Asset::Graphics::PLAYER_SKIN_02.data();

    //body
    GameObject* playerBody = nullptr;
    GameObject* playerLegLeft = nullptr;
    GameObject* playerLegRight = nullptr;
    GameObject* playerCape = nullptr;

    //scripts
    PlayerMove* playerMove = nullptr;
    PlayerAnim* playerAnim = nullptr;

    //components
    CircleCollider* collider;
    Rigidbody* rb;

protected:
    virtual void onAwake() override;
};

#endif // PLAYERCORE_H
