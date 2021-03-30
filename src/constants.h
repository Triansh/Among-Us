//
// Created by triansh on 25/03/21.
//

#ifndef AMONGUS_CONSTANTS_H
#define AMONGUS_CONSTANTS_H

const unsigned int FPS = 40;

const unsigned int SCREEN_WIDTH = 1600;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 800;

const glm::vec2 TILE_SIZE = glm::vec2(200.0f, 150.0f);

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 10;

enum MovementType {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE,
};

#endif //AMONGUS_CONSTANTS_H
