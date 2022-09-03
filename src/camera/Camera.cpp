#include "camera/Camera.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace arcana {
    // CAMERA IMPL.
    Camera::Camera() {
        dimensions = Vector2(0,0);
        offset = Vector2(0,0);
        rotation = 0.0f;
        zoom = 1.0f;
    }

    Camera::~Camera() {

    }

    void Camera::setDim(int width, int height) {
        dimensions.x = width;
        dimensions.y = height;
    }

    void Camera::setZoom(float zoom) {
        this->zoom = zoom;
    }

    Mat4 Camera::getProjectionMatrix() {
        Mat4 projectionMat = glm::ortho(0.0f, dimensions.x, dimensions.y, 0.0f, -1.0f, 1.0f);
        glm::translate(projectionMat, Vector3(offset, 0.0f));
        glm::scale(projectionMat, Vector3(offset, 1.0f));
        return projectionMat;
    }
}