//
// Created by triansh on 23/03/21.
//

#ifndef AMONGUS_GAME_H
#define AMONGUS_GAME_H
/*******************************************************************
** This code is part of AmongUs.
**
** AmongUs is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Sprite.h"
#include "Player.h"
#include "Maze.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_LOST,
    GAME_WIN
};

typedef struct Info {
    float score;
    int tasksCompleted;
    int clock;
    bool lighting;
    glm::vec4 lightArea;

    Info() {
        score = 1;
        tasksCompleted = 0;
        clock = 180;
        lighting = true;
        lightArea = glm::vec4(0.0f);
    }

} Info;

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game {
public:
    // game state
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;
    int index;
    Info info;

    // constructor/destructor
    Game(unsigned int width, unsigned int height);

    ~Game();

    // initialize game state (load all shaders/textures/levels)
    void Init();

    // game loop
    void ProcessInput(float dt);

    void SetProjection();


    void Update();

    void Render();

    static void loadPlayer();


    static void loadTiles();

    static void loadImposter();


    static bool movePlayer(MovementType dir, MovementType oppDir);

    void moveImposter();

    void SetImposterPosition();

    static bool CheckCollisions(Sprite *sprite, Sprite *collider);

    static bool CheckTileCollisions(Sprite *sprite);

    static void clearColor(glm::vec4 color);

    void switchLights(bool lightOff);

    bool checkInsideLightArea(glm::vec2 pos);

    void renderHUD() const;
};

#endif
#endif //AMONGUS_GAME_H
