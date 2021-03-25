//
// Created by triansh on 25/03/21.
//

#include <iostream>
#include "Camera2D.h"
#include "window.h"

Camera2D::Camera2D(glm::vec2 focusPosition, float zoom) {
    this->focusPosition = focusPosition;
    this->zoom = zoom;
}

glm::mat4 Camera2D::GetProjection(glm::vec2 target) {

    focusPosition = target;
    float left = focusPosition.x - SCREEN_WIDTH / 2.0f;
    float right = focusPosition.x + SCREEN_WIDTH / 2.0f;
    float top = focusPosition.y - SCREEN_HEIGHT / 2.0f;
    float bottom = focusPosition.y + SCREEN_HEIGHT / 2.0f;

    glm::mat4 ortho = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, zoom));

    return scale * ortho ;
}

void Camera2D::SetZoom(float zoomIn) {
  zoom = zoomIn;
}

