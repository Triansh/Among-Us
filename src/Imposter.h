//
// Created by triansh on 26/03/21.
//

#ifndef AMONGUS_IMPOSTER_H
#define AMONGUS_IMPOSTER_H


#include "AnimatedSprite.h"
#include "constants.h"


class Imposter : public AnimatedSprite {

public:
    Imposter();

    void move();

    float speed;
    glm::vec2 target;

    void setHitbox() override;

    bool checkTarget();

};


#endif //AMONGUS_IMPOSTER_H
