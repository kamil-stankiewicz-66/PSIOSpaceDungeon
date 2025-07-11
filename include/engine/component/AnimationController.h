#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "engine/component/Component.h"
#include "engine/component/Transform.h"
#include <map>
#include <memory>
#include <vector>
using namespace std;
using uint = unsigned int;


///
/// \brief Abstract class representing one single step in animation.
///

class AnimationStep
{
    friend class AnimationCycle;

protected:
    float duration; //in seconds

public:
    AnimationStep(const float& durationInSeconds);

protected:

    ///
    /// \brief Animation update in every frame.
    /// \return True - if animation ends.
    ///

    virtual bool update(const float& deltatime) = 0;


    ///
    /// \brief Reset all calculation variables.
    /// \details This method is called automatically after the movement is completed.
    ///

    virtual void reset() = 0;
};


///
/// \brief Class representing one single step in transform animation.
///

class AnimationTransformStep : public AnimationStep
{
    Transform* transform;

    //init states
    const Vector2 initPosition;
    const Vector2 initScale;
    const float initRotation;

    //target states
    const Vector2 targetPosition;
    const Vector2 targetScale;
    const float targetRotation;

    //variables for calculation
    Vector2 stepPosition; //per mili second
    Vector2 stepScale; //per mili second
    float stepRotation; //per mili second

    //variables for calculation
    Vector2 curentPosition;
    Vector2 currentScale;
    float currentRotation;

public:
    AnimationTransformStep(Transform* transform,
                           const Vector2& initPosition,
                           const Vector2& targetPosition,
                           const Vector2& initScale,
                           const Vector2& targetScale,
                           const float& initRotation,
                           const float& targetRotation,
                           const float& durationInSeconds);

private:
    virtual bool update(const float& deltatime) override;
    virtual void reset() override;
};


///
/// \brief A class representing a cycle of sequentially run animation steps.
///

class AnimationCycle
{
    friend class Animation;
    vector<shared_ptr<AnimationStep>> cycle;
    uint step;

public:
    AnimationCycle(const vector<shared_ptr<AnimationStep>>& cycle);

private:

    ///
    /// \brief Animation update in every frame.
    /// \return True - if animation cycle end.
    ///

    bool update(const float& deltatime);

    void reset();
};


///
/// \brief A class representing parallel animation cycles.
///

class Animation
{
    friend class AnimationController;
    vector<AnimationCycle> animation;
    map<uint, bool> data; //is cycle completed

public:
    Animation(const vector<AnimationCycle>& animation);

private:

    ///
    /// \brief Animation update in every frame.
    /// \return True - if all cycles ends.
    ///

    bool update(const float& deltatime);

    void reset();
};


///
/// \brief Component for managing animations.
///

class AnimationController : public Component
{
    vector<Animation> animations;
    int runningAnim = -1; //-1 means no animation is running

protected:
    virtual void onUpdate(float deltaTime) override;

public:

    ///
    /// \brief Add new animation.
    /// \return animation id
    ///

    const uint add(const Animation&);


    ///
    /// \brief Start animation.
    /// \param animID animation id
    ///

    void play(const uint& animID);


    ///
    /// \brief Stop animation...
    /// \details ...and reset all elements.
    ///

    void reset();


    //getter
    const int& getCurrentAnimation() const;
};

#endif // ANIMATIONCONTROLLER_H
