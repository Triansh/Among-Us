//
// Created by triansh on 26/03/21.
//

#include "AnimatedSprite.h"
#include "resourceManager.h"

AnimatedSprite::AnimatedSprite(const std::string &textureName, glm::vec2 position, glm::vec2 scale, float rotation,
                               glm::vec3 color) : Sprite(textureName, position, scale, rotation, color) {

    anims = {};
    currAnim = None;
}

void AnimatedSprite::addAnimation(AnimationType type, Animation2D *animation) {
    anims[type] = animation;
    currAnim = type;
}

void AnimatedSprite::draw() {
    if (currAnim != None) {
        auto animation = anims[currAnim];
        animation->play();
        texture = ResourceManager::GetTexture(animation->getAnimation());
    }
}