//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_TRANSFORM_H
#define AMONGUS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    glm::vec2 position;
    glm::vec2 scale;
    float angle;

    Transform(glm::vec2 position, glm::vec2 scale, float angle);

    Transform();

    glm::mat4 Get();
};

#endif //AMONGUS_TRANSFORM_H
