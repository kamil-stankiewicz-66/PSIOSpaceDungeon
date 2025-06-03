#include "engine/core/VMath.h"

const bool VMath::sameDirection(const Vector2& a, const Vector2& b) {
    if (a.zero() || b.zero()) {
        return false;
    }

    return a.x * b.x + a.y * b.y > 0.0f;
}
