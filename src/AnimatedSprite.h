#ifndef AMONGUS_ANIMATEDSPRITE_H
#define AMONGUS_ANIMATEDSPRITE_H

#include "Animation2D.h"
#include "Sprite.h"
#include "constants.h"

enum AnimationType {
    IdleLeft,
    RunLeft,
    IdleRight,
    RunRight,
    None,
};

class AnimatedSprite : public Sprite {

public:
    AnimationType currAnim;

    map<AnimationType, Animation2D *> anims;

    AnimatedSprite(const string &textureName, glm::vec2 position, glm::vec2 scale = glm::vec2(20.0f, 20.0f),
                   float rotation = 0, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

    void addAnimation(AnimationType type, Animation2D *animation);

    void draw();

    void stopAnimation(AnimationType animName);
};


#endif //AMONGUS_ANIMATEDSPRITE_H
