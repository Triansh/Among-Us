
#include "Sprite.h"
#include "resourceManager.h"


Sprite::Sprite(const std::string &textureName, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec3 color) {
    texture = ResourceManager::GetTexture(textureName);
    transformation = Transform(position, scale, rotation);
    this->color = color;
    hitboxPos = position;
    hitboxSize = scale;
}

void Sprite::addPosition(glm::vec2 pos) {
    transformation.position += pos;
}

glm::vec2 Sprite::getPosition() const {
    return transformation.position;
}

glm::vec2 Sprite::getSize() const {
    return transformation.scale;
}

void Sprite::setHitbox() {}

glm::vec2 Sprite::getCenter() const {
    return transformation.position + (transformation.scale / 2.0f);
}

void Sprite::setCenter(glm::vec2 pos) {
    transformation.position = pos - transformation.scale / 2.0f;
    setHitbox();
}

void Sprite::setColor(glm::vec3 color) {
    this->color = color;
}




