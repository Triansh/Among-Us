//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_MAZE_H
#define AMONGUS_MAZE_H


#include "Tile.h"
#include "PowerUp.h"

class Maze {

public:
    Maze();

    void createMaze();

    vector<Tile *> tiles;
    vector<PowerUp *> obstacles;
    vector<string> pat;
    int M, N;

    vector<vector<int>> adj;

    void generateGraph();

    int getIdFromPos(glm::vec2 pos) const;

    char runDjkstra(glm::vec2 destination, glm::vec2 begin);

    char getDirection(int beginId, int nextId) const;

    glm::vec2 getImposterPos();

    void displayMaze();

    void makeTiles();

    int verifyDestination(glm::vec2 vec);

    glm::vec2 getTaskTilePosition(int k);

    void makeObstacles();

    glm::vec4 changeColor(glm::vec2 pos, glm::vec3 color);
};


#endif //AMONGUS_MAZE_H
