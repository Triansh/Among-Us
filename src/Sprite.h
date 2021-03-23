
#ifndef AMONGUS_SPRITE_H
#define AMONGUS_SPRITE_H

#include<glm/glm.hpp>

#include <iostream>
#include<map>
using namespace std;

#include "texture.h"
#include "transform.h"
#include "Animation2D.h"


enum AnimationType {
    Idle,
    Run,
    None,
};


class Sprite {
public:
    Texture2D texture;
    Transform transformation;
    glm::vec3 color{};
    AnimationType currentAnim;

    map<AnimationType, Animation2D *> anims;

    Sprite(const string &textureName, glm::vec2 position, glm::vec2 scale = glm::vec2(20.0f), float rotation = 0,
           glm::vec3 color = glm::vec3(1.0f));

    void addAnimation(AnimationType type, Animation2D *animation);

    void draw();


};


#endif //AMONGUS_SPRITE_H
