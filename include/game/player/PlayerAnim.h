#ifndef PLAYERANIM_H
#define PLAYERANIM_H

#include "engine/object/Object.h"

using uint = unsigned int;
class PlayerCore;
class AnimationController;

class PlayerAnim : public Object
{
    friend PlayerCore;

    //animations
    uint ANIM_IDLE;
    uint ANIM_RUN;

private:
    PlayerCore* playerCore = nullptr;
    AnimationController* animationController = nullptr;

protected:
    virtual void onAwake() override;
    virtual void onUpdate(float) override;
};

#endif // PLAYERANIM_H
