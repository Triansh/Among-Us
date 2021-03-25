//
// Created by triansh on 25/03/21.
//

#include "Tile.h"


Tile::Tile(const string &textureName, glm::vec2 position, glm::vec2 scale, bool isWall, float rotation, glm::vec3 color)
        : Sprite(textureName, position, scale, rotation, color) {
    this->isWall = isWall;

}
