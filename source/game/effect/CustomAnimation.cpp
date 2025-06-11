#include "game/effect/CustomAnimation.h"

AnimationTextureStep::AnimationTextureStep(VSprite* sprite,
                                           sf::Texture* nextTexture,
                                           const sf::IntRect& nextRect,
                                           const float& duration) : AnimationStep(duration)
{
    this->sprite = sprite;
    this->nextTxt = nextTexture;
    this->nextRect = nextRect;
}

bool AnimationTextureStep::update(const float& dt)
{
    bool flag = false;


    if (timeAcc >= (duration * 1000.f))
    {
        sprite->setTexture(nextTxt);
        sprite->setTextureRect(nextRect);
        flag = true;
    }

    timeAcc += dt;
    return flag;
}

void AnimationTextureStep::reset()
{
    this->timeAcc = 0.f;
}
