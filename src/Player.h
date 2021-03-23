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


class Player {


public:
    Player(float speed = 4.0f);

    Sprite *sprite;
    float speed;

    void draw();


    void move(MovementType mt);

    void stop();
};


#endif //AMONGUS_PLAYER_H
