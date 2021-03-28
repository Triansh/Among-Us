
#ifndef AMONGUS_SPRITE_H
#define AMONGUS_SPRITE_H

#include<glm/glm.hpp>

#include <iostream>
#include<map>
using namespace std;

#include "texture.h"
#include "transform.h"
#include "Animation2D.h"

class Sprite {
public:
    Texture2D texture;
    Transform transformation;
    glm::vec3 color{};


    Sprite(const string &textureName, glm::vec2 position, glm::vec2 scale = glm::vec2(20.0f, 20.0f), float rotation = 0,
           glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

    glm::vec2 hitboxPos{};
    glm::vec2 hitboxSize{};

    glm::vec2 getPosition() const;

    glm::vec2 getCenter() const;

    void setCenter(glm::vec2 pos);

    virtual void setHitbox();

    void addPosition(glm::vec2 pos);
};


#endif //AMONGUS_SPRITE_H
