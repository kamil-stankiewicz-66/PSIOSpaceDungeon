#ifndef PLAYERCORE_H
#define PLAYERCORE_H

#include "engine/component/Collider.h"
#include "engine/object/Object.h"
#include "game/core/Asset.h"
#include "game/player/PlayerEnemyDetector.h"
#include "game/physics/Rigidbody.h"
#include "game/player/PlayerAnim.h"
#include "game/player/PlayerAttack.h"
#include "game/player/PlayerHealthSystem.h"
#include "game/player/PlayerMove.h"
#include "game/player/PlayerSpecialEffects.h"

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
    friend class PlayerEnemyDetector;
    friend class PlayerSpecialEffects;

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
    CircleCollider* collider = nullptr;
    Rigidbody* rb = nullptr;
    PlayerHealthSystem* healthSystem = nullptr;
    PlayerSpecialEffects* playerSpecialEffects = nullptr;

protected:
    virtual void onAwake() override;
};

#endif // PLAYERCORE_H
