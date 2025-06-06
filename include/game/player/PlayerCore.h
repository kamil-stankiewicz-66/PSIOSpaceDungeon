#ifndef PLAYERCORE_H
#define PLAYERCORE_H

#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "game/core/Asset.h"
#include "game/player/PlayerEnemyDetector.h"
#include "game/weapon/Weapon.h"
#include "game/physics/Rigidbody.h"
#include "game/player/PlayerAnim.h"
#include "game/player/PlayerAttack.h"
#include "game/player/PlayerMove.h"

///
/// The PlayerCore class.
/// Main player object.
///

class PlayerCore : public GameObject
{
    friend class LevelManager;
    friend class PlayerMove;
    friend class PlayerAnim;
    friend class PlayerAttack;

private:
    const string m_bodyTexture = Asset::Graphics::PLAYER_SKIN_02.data();

    //body
    GameObject* playerRect = nullptr;
    GameObject* playerBody = nullptr;
    GameObject* playerLegLeft = nullptr;
    GameObject* playerLegRight = nullptr;
    GameObject* playerCape = nullptr;
    GameObject* hand = nullptr;

    //scripts
    PlayerMove* playerMove = nullptr;
    PlayerAnim* playerAnim = nullptr;
    PlayerAttack* playerAttack = nullptr;
    PlayerEnemyDetector* playerDetector = nullptr;

    //components
    CircleCollider* collider;
    Rigidbody* rb;

protected:
    virtual void onAwake() override;
};

#endif // PLAYERCORE_H
