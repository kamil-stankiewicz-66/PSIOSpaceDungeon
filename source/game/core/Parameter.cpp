#include "game/core/Parameter.h"

float Parameters::PlayerControl::move_speed = 8.0f;

const float& Parameters::PlayerControl::getMoveSpeed() {
    return Parameters::PlayerControl::move_speed;
}
