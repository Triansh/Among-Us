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
    int M, N;

    vector<vector<int>> adj;

    void generateGraph();

    int getIdFromPos(glm::vec2 pos) const;

    void runDjkstra(glm::vec2 destination);

    char runDjkstra(glm::vec2 destination, glm::vec2 begin);

    char getDirection(int beginId, int nextId) const;
};


#endif //AMONGUS_MAZE_H
