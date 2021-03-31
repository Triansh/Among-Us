#include "Transform.h"

Transform::Transform(glm::vec2 position, glm::vec2 scale, float angle) {
    this->position = position;
    this->scale = scale;
    this->angle = angle;
}

Transform::Transform() {
    position = glm::vec2(200.0f);
    scale = glm::vec2(20.0f);
    angle = 0.0f;
}

glm::mat4 Transform::Get() {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0f));
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

    return translation * scaling * rotation;
}


