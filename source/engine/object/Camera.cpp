#include "engine/object/Camera.h"
#include <cmath>

Camera::Camera() : view_size(1)
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

void Camera::set_rotation(const float& _r)
{
    //this->rotation = _r;
    this->rotation = std::fmod(_r, FULL_ROTATION);
}


///
/// getters
///

const float& Camera::get_viewSize() const {
    return this->view_size;
}

const float& Camera::get_rotation() const {
    return this->rotation;
}
