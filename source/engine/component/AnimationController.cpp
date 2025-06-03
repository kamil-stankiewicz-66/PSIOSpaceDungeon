#include "engine/component/AnimationController.h"
#include "engine/core/VMath.h"
#include <cmath>


///
/// AnimationMove
///

AnimationMove::AnimationMove(const float& durationInSeconds)
    : duration(durationInSeconds)
{
}


///
/// AnimationTransformMove
///

AnimationTransformMove::AnimationTransformMove(Transform* transform,
                                               const Vector2& initPosition,
                                               const Vector2& targetPosition,
                                               const Vector2& initScale,
                                               const Vector2& targetScale,
                                               const float& initRotation,
                                               const float& targetRotation,
                                               const float& durationInSeconds)
    : AnimationMove(durationInSeconds), transform(transform),
    targetPosition(targetPosition), targetScale(targetScale), targetRotation(targetRotation),
    initPosition(initPosition), initScale(initScale), initRotation(initRotation)
{
    if (!transform) {
        return;
    }

    //steps
    stepPosition = (targetPosition - initPosition) / (durationInSeconds * 1000.0f);
    stepScale = (targetScale - initScale) / (durationInSeconds * 1000.0f);
    stepRotation = (targetRotation - initRotation) / (durationInSeconds * 1000.0f);

    //set calculation vars
    AnimationTransformMove::reset();
}

bool AnimationTransformMove::update(const float& deltatime)
{
    curentPosition = curentPosition + (stepPosition * deltatime);
    currentScale = currentScale + (stepScale * deltatime);
    currentRotation = currentRotation + (stepRotation * deltatime);

    bool flagPosition = false;
    {
        Vector2 remainingPosition = targetPosition - curentPosition;
        if (VMath::sameDirection(remainingPosition, stepPosition)) {
            transform->set_position(curentPosition);
        }
        else {
            transform->set_position(targetPosition);
            flagPosition = true;
        }
    }

    bool flagScale = false;
    {
        Vector2 remainingScale = targetScale - currentScale;
        if (VMath::sameDirection(remainingScale, stepScale)) {
            transform->set_scale(currentScale);
        }
        else {
            transform->set_scale(targetScale);
            flagScale = true;
        }
    }

    bool flagRotation = false;
    {
        bool outOfRotation = (targetRotation - currentRotation) * (targetRotation - initRotation) <= 0.0f;
        if (!outOfRotation) {
            transform->set_rotation(currentRotation);
        }
        else {
            transform->set_rotation(targetRotation);
            flagRotation = true;
        }
    }

    return flagPosition && flagScale && flagRotation;
}

void AnimationTransformMove::reset()
{
    this->curentPosition = this->initPosition;
    this->currentScale = this->initScale;
    this->currentRotation = this->initRotation;
}


///
/// AnimationCycle
///

AnimationCycle::AnimationCycle(const vector<shared_ptr<AnimationMove>>& cycle)
    : cycle(cycle), step(0)
{
}

bool AnimationCycle::update(const float& deltatime)
{
    if (cycle.empty()) {
        return true;
    }

    if (step >= cycle.size()) {
        step = 0;
    }

    bool flag = cycle[step]->update(deltatime);

    if (flag) {
        cycle[step]->reset();
        ++step;
    }

    return flag && (step >= cycle.size());
}


///
/// Animation
///

Animation::Animation(const vector<AnimationCycle>& animation)
    : animation(animation)
{
}

bool Animation::update(const float& deltatime)
{
    bool flag = true;

    for (AnimationCycle& cycle: animation)
    {
        if (!cycle.update(deltatime)) {
            flag = false;
        }
    }

    return flag;
}


///
/// AnimationController
///

void AnimationController::onUpdate(float deltaTime)
{
    if (runningAnim == -1) {
        return;
    }

    if (animations[runningAnim].update(deltaTime)) {
        runningAnim = -1;
    }
}

const uint AnimationController::add(const Animation& animation) {
    animations.emplace_back(animation);
    return animations.size()-1;
}

void AnimationController::play(const uint& animID)
{
    if (animID < animations.size()) {
        runningAnim = animID;
    }
}











