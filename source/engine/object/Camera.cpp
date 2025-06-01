#include "engine/object/Camera.h"
#include <cmath>

Camera::Camera() : view_size(1.0f)
{
    this->addTag("camera");
}


///
/// setters
///

void Camera::set_viewSize(const float& _v)
{
    if (_v < MIN_VIEWSIZE)
    {
        this->view_size = MIN_VIEWSIZE;
    }
    else
    {
        this->view_size = _v;
    }
}


///
/// getters
///

const float& Camera::get_viewSize() const {
    return this->view_size;
}
