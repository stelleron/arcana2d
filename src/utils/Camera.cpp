#include "utils/Camera.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace arcana {
    // CAMERA IMPL.
    Camera::Camera() {

    }

    Camera::~Camera() {

    }

    void Camera::defaultSettings(int width, int height) {
        camera_dim.x = width;
        camera_dim.y = height;
    }

    glm::mat4 Camera::getProjectionMatrix() {
        return glm::ortho(0.0f, camera_dim.x, camera_dim.y, 0.0f, -1.0f, 1.0f);
    }
}