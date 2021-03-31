//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_PLAYER_H
#define AMONGUS_PLAYER_H


#include "AnimatedSprite.h"
#include "constants.h"

class Player : public AnimatedSprite {

public:
    Player();

    float speed;

    void move(MovementType mt);

    void stop();

    void setHitbox() override;
};


#endif //AMONGUS_PLAYER_H
