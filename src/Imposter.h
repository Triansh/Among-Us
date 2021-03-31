#ifndef AMONGUS_IMPOSTER_H
#define AMONGUS_IMPOSTER_H

#include "AnimatedSprite.h"
#include "constants.h"


class Imposter : public AnimatedSprite {

public:
    Imposter();

    void move();

    float speed;
    bool isDead;
    glm::vec2 target{};

    void setHitbox() override;

    bool checkTarget();
};


#endif //AMONGUS_IMPOSTER_H
