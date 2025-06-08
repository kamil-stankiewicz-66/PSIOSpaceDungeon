#include "game/effect/CustomAnimation.h"

AnimationTextureMove::AnimationTextureMove(VSprite* sprite,
                                           const shared_ptr<sf::Texture>& nextTexture,
                                           const sf::IntRect& nextRect,
                                           const float& duration) : AnimationMove(duration)
{
    this->sprite = sprite;
    this->nextTxt = nextTexture;
    this->nextRect = nextRect;
}

bool AnimationTextureMove::update(const float& dt)
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

void AnimationTextureMove::reset()
{
    this->timeAcc = 0.f;
}
