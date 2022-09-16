#include "camera/Camera.hpp"
#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace arcana {
    // CAMERA IMPL.
    Camera::Camera() {
        dimensions = Vector2(0,0);
    }

    Camera::~Camera() {

    }

    Mat4 Camera::getProjectionMatrix() {
        // First create the projection matrix
        Mat4 projectionMat = glm::ortho(0.0f, dimensions.x, dimensions.y, 0.0f, -100.0f, 100.0f);
        return projectionMat;
    }
}