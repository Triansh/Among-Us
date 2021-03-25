//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_PLAYER_H
#define AMONGUS_PLAYER_H


#include "Sprite.h"

enum MovementType {
    LEFT,
    RIGHT,
    UP,
    DOWN,
};


class Player : public Sprite {


public:
    Player();

    float speed;
    glm::vec2 hitboxPos{}, hitboxSize{};

    void move(MovementType mt);

    void stop();

    void setHitboxes();
};


#endif //AMONGUS_PLAYER_H
