//
// Created by triansh on 25/03/21.
//

#include <iostream>
#include "Camera2D.h"
#include "constants.h"

using namespace std;

Camera2D::Camera2D(glm::vec2 focusPosition, float zoom) {
    this->focusPosition = focusPosition;
    this->zoom = zoom;
}

glm::mat4 Camera2D::GetProjection(glm::vec2 target) {

    focusPosition = target;
    float width = SCREEN_WIDTH / zoom, height = SCREEN_HEIGHT / zoom;
    left = min(max(0.0f - 50, focusPosition.x - width / 2.0f),
               (2 * MAZE_WIDTH + 1) * TILE_SIZE.x - width + 50);
    right = left + width;
    top = min(max(0.0f - 50, focusPosition.y - height / 2.0f),
              (2 * MAZE_HEIGHT + 1) * TILE_SIZE.y - height + 50);
    bottom = top + height;

    glm::mat4 ortho = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
//    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, zoom));

    return ortho;
}

void Camera2D::SetZoom(float zoomIn) {
    zoom = max(0.40f, min(zoomIn, 1.50f));

}

