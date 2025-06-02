#ifndef PLAYERCORE_H
#define PLAYERCORE_H

#include "engine/object/Object.h"
#include "game/player/PlayerMove.h"

class PlayerBody;

class PlayerCore : public GameObject
{
private:
    PlayerBody* playerBody = nullptr;
    PlayerMove* playerMove = nullptr;

protected:
    virtual void onAwake() override;
};


class PlayerBody : public GameObject
{
protected:
    virtual void onAwake() override;
};

#endif // PLAYERCORE_H
