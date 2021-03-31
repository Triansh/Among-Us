#include "Tile.h"


Tile::Tile(const string &textureName, glm::vec2 position, glm::vec2 scale, bool isWall, float rotation, glm::vec3 color)
        : Sprite(textureName, position, scale, rotation, color) {
    this->isWall = isWall;
    setHitbox();
}

void Tile::setHitbox() {
    hitboxPos = glm::vec2(transformation.position) + glm::vec2(0.0f, 12.0f);
    hitboxSize = glm::vec2(transformation.scale) - glm::vec2(0.0f, 14.0f);
}
