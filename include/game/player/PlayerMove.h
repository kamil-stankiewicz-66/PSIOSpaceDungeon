#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "engine/object/Object.h"

class PlayerCore;

class PlayerMove : public Object
{
    friend PlayerCore;

private:
    PlayerCore* playerCore = nullptr;

    Vector2 m_move_dir; //move direction

protected:
    virtual void onAwake() override;
    virtual void onUpdate(float) override;

private:
    void move();
};

#endif // PLAYERMOVE_H
