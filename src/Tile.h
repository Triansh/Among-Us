#ifndef AMONGUS_TILE_H
#define AMONGUS_TILE_H


#include "Sprite.h"

class Tile : public Sprite {
public:
    bool isWall;

    Tile(const string &textureName, glm::vec2 position, glm::vec2 scale, bool isWall = false, float rotation = 0.0f,
         glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

    void setHitbox() override;

};

#endif //AMONGUS_TILE_H
