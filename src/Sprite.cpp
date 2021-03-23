
#include "Sprite.h"
#include "resourceManager.h"


Sprite::Sprite(const std::string &textureName, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec3 color) {
    texture = ResourceManager::GetTexture(textureName);
    transformation = Transform(position, scale, rotation);
    this->color = color;
    anims = {};
    currentAnim = None;

}

void Sprite::addAnimation(AnimationType type, Animation2D *animation) {
    anims[type] = animation;
    currentAnim = type;
}

void Sprite::draw() {

    if (currentAnim != None) {
        auto animation = anims[currentAnim];
        animation->play();
        texture = ResourceManager::GetTexture(animation->getAnimation());
    }
}



