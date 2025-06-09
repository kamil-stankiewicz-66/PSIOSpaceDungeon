#include "game/player/PlayerAnim.h"
#include "game/player/PlayerCore.h"
#include "engine/component/AnimationController.h"
#include "engine/core/Engine.h"

void PlayerAnim::onAwake()
{
    playerCore = getGame()->get_currentScene()->findObject<PlayerCore>();

    if (!playerCore) {
        VDebuger::print("<ERROR>[GAME] :: PLAYER_ANIM :: playerCore = nullptr");
        return;
    }


    //animation controller
    animationController = createComponent<AnimationController>();


    //transforms
    Transform* body = playerCore->playerBody->getTransformPtr();
    Transform* cape = playerCore->playerCape->getTransformPtr();
    Transform* leftLeg = playerCore->playerLegLeft->getTransformPtr();
    Transform* rightLeg = playerCore->playerLegRight->getTransformPtr();


    //idle anim
    {
        float duration = 0.2f;
        Vector2 range = Vector2(0.0f, 5.0f);

        //body

        auto bodyAnimDown = make_shared<AnimationTransformStep>(body,
                                                                body->get_localPosition(),
                                                                body->get_localPosition() - range,
                                                                body->get_scale(),
                                                                body->get_scale(),
                                                                body->get_rotation(),
                                                                body->get_rotation(),
                                                                duration);

        auto bodyAnimUp = make_shared<AnimationTransformStep>(body,
                                                              body->get_localPosition() - range,
                                                              body->get_localPosition(),
                                                              body->get_scale(),
                                                              body->get_scale(),
                                                              body->get_rotation(),
                                                              body->get_rotation(),
                                                              duration);

        AnimationCycle bodyCycle({bodyAnimDown, bodyAnimUp});


        //cape
        auto capeAnim = make_shared<AnimationTransformStep>(cape,
                                                            cape->get_localPosition(),
                                                            cape->get_localPosition(),
                                                            cape->get_scale(),
                                                            cape->get_scale(),
                                                            cape->get_rotation(),
                                                            cape->get_rotation(),
                                                            1.0f);

        AnimationCycle capeCycle({capeAnim});


        //left leg

        auto leftLegAnim = make_shared<AnimationTransformStep>(leftLeg,
                                                                 leftLeg->get_localPosition(),
                                                                 leftLeg->get_localPosition(),
                                                                 leftLeg->get_scale(),
                                                                 leftLeg->get_scale(),
                                                                 leftLeg->get_rotation(),
                                                                 leftLeg->get_rotation(),
                                                                 duration);

        AnimationCycle leftLegCycle({leftLegAnim});


        //right leg

        auto rightLegAnim = make_shared<AnimationTransformStep>(rightLeg,
                                                                  rightLeg->get_localPosition(),
                                                                  rightLeg->get_localPosition(),
                                                                  rightLeg->get_scale(),
                                                                  rightLeg->get_scale(),
                                                                  rightLeg->get_rotation(),
                                                                  rightLeg->get_rotation(),
                                                                  duration);

        AnimationCycle rightLegCycle({rightLegAnim});


        //make animation
        Animation idleAnim({bodyCycle, capeCycle, leftLegCycle, rightLegCycle});
        ANIM_IDLE = animationController->add(idleAnim);
    }

    //run anim
    {
        float duration = 0.1f;
        float capeAnimDurationMulplier = 1.4f;
        float legShift = -5.0f;

        //body

        auto bodyAnim01 = make_shared<AnimationTransformStep>(body,
                                                              body->get_localPosition(),
                                                              body->get_localPosition(),
                                                              body->get_scale(),
                                                              body->get_scale(),
                                                              body->get_rotation() + 5.0f,
                                                              body->get_rotation() + 10.0f,
                                                              duration * capeAnimDurationMulplier);

        auto bodyAnim02 = make_shared<AnimationTransformStep>(body,
                                                              body->get_localPosition(),
                                                              body->get_localPosition(),
                                                              body->get_scale(),
                                                              body->get_scale(),
                                                              body->get_rotation() + 10.0f,
                                                              body->get_rotation() + 5.0f,
                                                              duration * capeAnimDurationMulplier);

        AnimationCycle bodyCycle({bodyAnim01, bodyAnim02});


        //cape

        auto capeAnim01 = make_shared<AnimationTransformStep>(cape,
                                                              cape->get_localPosition() + Vector2(-5.0f, 8.0f),
                                                              cape->get_localPosition() + Vector2(-10.0f, 12.0f),
                                                              cape->get_scale(),
                                                              cape->get_scale(),
                                                              cape->get_rotation() + 10.0f,
                                                              cape->get_rotation() + 25.0f,
                                                              duration * capeAnimDurationMulplier);

        auto capeAnim02 = make_shared<AnimationTransformStep>(cape,
                                                              cape->get_localPosition() + Vector2(-10.0f, 12.0f),
                                                              cape->get_localPosition() + Vector2(-5.0f, 8.0f),
                                                              cape->get_scale(),
                                                              cape->get_scale(),
                                                              cape->get_rotation() + 25.0f,
                                                              cape->get_rotation() + 10.0f,
                                                              duration * capeAnimDurationMulplier);

        AnimationCycle capeCycle({capeAnim01, capeAnim02});


        //left leg

        auto leftLegAnimUp = make_shared<AnimationTransformStep>(leftLeg,
                                                                 leftLeg->get_localPosition() + Vector2(legShift, 0.0f),
                                                                 leftLeg->get_localPosition() + Vector2(legShift, 10.0f),
                                                                 leftLeg->get_scale(),
                                                                 leftLeg->get_scale(),
                                                                 leftLeg->get_rotation(),
                                                                 leftLeg->get_rotation(),
                                                                 duration);

        auto leftLegAnimDown = make_shared<AnimationTransformStep>(leftLeg,
                                                                   leftLeg->get_localPosition() + Vector2(legShift, 10.0f),
                                                                   leftLeg->get_localPosition() + Vector2(legShift, 0.0f),
                                                                   leftLeg->get_scale(),
                                                                   leftLeg->get_scale(),
                                                                   leftLeg->get_rotation(),
                                                                   leftLeg->get_rotation(),
                                                                   duration);

        AnimationCycle leftLegCycle({leftLegAnimUp, leftLegAnimDown});


        //right leg

        auto rightLegAnimUp = make_shared<AnimationTransformStep>(rightLeg,
                                                                  rightLeg->get_localPosition() + Vector2(legShift, 0.0f),
                                                                  rightLeg->get_localPosition() + Vector2(legShift, 10.0f),
                                                                  rightLeg->get_scale(),
                                                                  rightLeg->get_scale(),
                                                                  rightLeg->get_rotation(),
                                                                  rightLeg->get_rotation(),
                                                                  duration);

        auto rightLegAnimDown = make_shared<AnimationTransformStep>(rightLeg,
                                                                    rightLeg->get_localPosition() + Vector2(legShift, 10.0f),
                                                                    rightLeg->get_localPosition() + Vector2(legShift, 0.0f),
                                                                    rightLeg->get_scale(),
                                                                    rightLeg->get_scale(),
                                                                    rightLeg->get_rotation(),
                                                                    rightLeg->get_rotation(),
                                                                    duration);

        AnimationCycle rightLegCycle({rightLegAnimDown, rightLegAnimUp});


        //make animation
        Animation runAnim({bodyCycle, capeCycle, leftLegCycle, rightLegCycle});
        ANIM_RUN = animationController->add(runAnim);
    }
}

void PlayerAnim::onUpdate(float dt)
{
    if (playerCore->playerMove->isRunning()) {
        animationController->play(ANIM_RUN);
    }
    else {
        animationController->play(ANIM_IDLE);
    }
}
