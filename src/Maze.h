//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_MAZE_H
#define AMONGUS_MAZE_H


#include "Tile.h"

class Maze {


public:
    Maze();

    void createMaze();

    vector<Tile *> tiles;
    vector<string> pat;
};


#endif //AMONGUS_MAZE_H
