//
// Created by triansh on 23/03/21.
//

#ifndef AMONGUS_GAME_H
#define AMONGUS_GAME_H
/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
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
    GAME_MENU,
    GAME_WIN
};

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

    // constructor/destructor
    Game(unsigned int width, unsigned int height);

    ~Game();

    // initialize game state (load all shaders/textures/levels)
    void Init();

    // game loop
    void ProcessInput(float dt);

    void SetProjection();


    void Update(float dt);

    void Render();

    static void loadPlayer();


    static void loadTiles();

    static void loadImposter();


    static bool CheckCollisions(AnimatedSprite *sprite);

    static bool movePlayer(MovementType dir, MovementType oppDir);

    void moveImposter();

    void SetImposterPosition();
};

#endif
#endif //AMONGUS_GAME_H
