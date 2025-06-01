#ifndef CAMERA_H
#define CAMERA_H

#include "engine/object/Object.h"
#include <cfloat>

///
/// \brief Class representing a basic camera.
///

class Camera : public GameObject
{
private:
    static constexpr float MIN_VIEWSIZE = FLT_MIN;

    ///
    /// \brief Parameter specifying the visibility range.
    /// \details Specifies the size of the area that the camera can see at a given moment.
    /// Defines how much of the game world will be displayed on the screen.
    ///

    float view_size;

public:
    Camera();

    //setters
    void set_viewSize(const float&);

    //getters
    const float& get_viewSize() const;
};

#endif // CAMERA_H
