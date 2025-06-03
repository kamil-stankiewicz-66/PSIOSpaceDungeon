#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

#include "engine/object/Object.h"

class PlayerCore;

class PlayerMove : public Object
{
    friend PlayerCore;

    //calculation var
    Vector2 m_move_dir; //move direction

private:
    PlayerCore* playerCore = nullptr;

protected:
    virtual void onAwake() override;
    virtual void onUpdate(float) override;

public:
    const bool isRunning() const;

private:
    void move(float dt);
};

#endif // PLAYERMOVE_H
