#ifndef AMONGUS_CAMERA2D_H
#define AMONGUS_CAMERA2D_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {

public:
    glm::vec2 focusPosition{};
    float zoom;
    float left{}, top{}, right{}, bottom{};

    Camera2D(glm::vec2 focusPosition, float zoom = 1.0f);

    glm::mat4 GetProjection(glm::vec2 target);

    void SetZoom(float zoomIn);

};


#endif //AMONGUS_CAMERA2D_H
