#ifndef AMONGUS_POWERUP_H
#define AMONGUS_POWERUP_H

#include "Sprite.h"

enum PowerUpType {
    COIN,
    BOMB,
    KILL_IMPOSTER,
    ACTIVATE_OBS,
};

class PowerUp : public Sprite {


public:
    PowerUpType type;

    bool isActive;

    void setHitbox() override;

    bool activate();

    PowerUp(const string &textureName, glm::vec2 position, glm::vec2 scale, PowerUpType type, float rotation = 0.0f,
            glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};


#endif //AMONGUS_POWERUP_H
