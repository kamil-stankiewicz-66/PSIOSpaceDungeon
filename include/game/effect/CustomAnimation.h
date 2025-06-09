#ifndef CUSTOMANIMATION_H
#define CUSTOMANIMATION_H

#include "SFML/Graphics/Texture.hpp"
#include "engine/component/AnimationController.h"
#include "engine/component/Renderable.h"

///
/// \brief Change texture after duration time.
///

class AnimationTextureMove : public AnimationStep
{
    //accumulation
    float timeAcc;

    //data
    VSprite* sprite = nullptr;
    shared_ptr<sf::Texture> nextTxt;
    sf::IntRect nextRect;

public:
    AnimationTextureMove(VSprite* sprite,
                         const shared_ptr<sf::Texture>& nextTexture,
                         const sf::IntRect& nextRect,
                         const float& duration);

private:
    virtual bool update(const float& dt) override;
    virtual void reset() override;
};

#endif // CUSTOMANIMATION_H
