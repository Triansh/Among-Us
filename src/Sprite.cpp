
#include "Sprite.h"
#include "resourceManager.h"


Sprite::Sprite(const std::string &textureName, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec3 color) {
    texture = ResourceManager::GetTexture(textureName);
    transformation = Transform(position, scale, rotation);
    this->color = color;
    anims = {};
    currAnim = None;
}

void Sprite::addAnimation(AnimationType type, Animation2D *animation) {
    anims[type] = animation;
    currAnim = type;
}

void Sprite::draw() {

    if (currAnim != None) {
        auto animation = anims[currAnim];
        animation->play();
        texture = ResourceManager::GetTexture(animation->getAnimation());
    }
}

void Sprite::addPosition(glm::vec2 pos) {
    transformation.position += pos;
}

glm::vec2 Sprite::getPosition() const {
    return transformation.position;
}



