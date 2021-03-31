//
// Created by triansh on 29/03/21.
//

#include "PowerUp.h"

PowerUp::PowerUp(const string &textureName, glm::vec2 position, glm::vec2 scale, PowerUpType type, float rotation,
                 glm::vec3 color) : Sprite(textureName, position, scale, rotation, color) {

    this->type = type;
    isActive = false;
    setHitbox();
}

void PowerUp::setHitbox() {
    hitboxPos = getPosition();
    hitboxSize = transformation.scale;
}

bool PowerUp::activate() {
    auto x = isActive;
    isActive = true;
    return !x;
}
