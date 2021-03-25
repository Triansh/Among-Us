/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <iostream>
#include <cstdlib>
#include "game.h"
#include "resourceManager.h"
#include "spriteRenderer.h"
#include "Camera2D.h"


// Game-related State data
//#3C4A4A -> 60,74,74
SpriteRenderer *Renderer;
SpriteRenderer *SkewRenderer;
Camera2D *camera;
Player *player;
Maze *maze;
Tile *tile, *tile2;


Game::Game(unsigned int width, unsigned int height)
        : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {
    index = 0;
}

Game::~Game() {
    delete Renderer;
}


void Game::Init() {
    // load shaders
    ResourceManager::LoadShader("../src/shaders/sprite.vs", "../src/shaders/sprite.fs", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection =
            glm::ortho(0.0f, static_cast<float>(this->Width),
                       static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    SkewRenderer = new SpriteRenderer(spriteShader, true);

    // load textures
    std::cout << "\n=====================================================================\n";
    std::cout << getenv("PWD") << "\n";
    std::cout << "\n=====================================================================\n";


    loadPlayer();
    loadTiles();


    player = new Player();
    maze = new Maze();
    camera = new Camera2D(player->getPosition());
    tile = new Tile("zz", player->hitboxPos, player->hitboxSize, false);
    tile2 = new Tile("stone-tile", player->hitboxPos, player->hitboxSize / 2.0f, false);
    SetProjection();
}


void Game::loadPlayer() {
    for (int i = 0; i < 24; i++) {
        std::string fileR, fileL, nameL, nameR;
        fileL = "../assets/sprites/player/run-left/tile0";
        fileR = "../assets/sprites/player/run-right/tile0";
        fileL = fileL.append(i < 10 ? "0" : "") + std::to_string(i) + ".png";
        fileR = fileR.append(i < 10 ? "0" : "") + std::to_string(i) + ".png";

        nameL = "player-left_";
        nameR = "player-right_";
        nameL = nameL.append(i < 10 ? "0" : "") + std::to_string(i);
        nameR = nameR.append(i < 10 ? "0" : "") + std::to_string(i);

        ResourceManager::LoadTexture(fileL, true, nameL);
        ResourceManager::LoadTexture(fileR, true, nameR);
    }
    ResourceManager::LoadTexture("../assets/sprites/player/stand-left.png", true, "player-left-idle");
    ResourceManager::LoadTexture("../assets/sprites/player/stand-right.png", true, "player-right-idle");

}

void Game::loadTiles() {
    ResourceManager::LoadTexture("../assets/tiles/stone-tile.png", true, "stone-tile");
    ResourceManager::LoadTexture("../assets/tiles/skeld-tile.png", true, "skeld-tile");
    ResourceManager::LoadTexture("../assets/tiles/skeld-wall.png", true, "skeld-wall");
    ResourceManager::LoadTexture("../assets/tiles/grass-tile.png", true, "grass-tile");
    ResourceManager::LoadTexture("../assets/tiles/brick-tile.png", true, "brick-tile");
    ResourceManager::LoadTexture("../assets/tiles/start-tile.png", true, "start-tile");
    ResourceManager::LoadTexture("../assets/tiles/trophy-tile.png", true, "trophy-tile");
}

void Game::Update(float dt) {
    SetProjection();
    tile->transformation.position = player->hitboxPos;
    tile->transformation.scale = player->hitboxSize;

}

void Game::SetProjection() {
    glm::mat4 projection = camera->GetProjection(player->transformation.position);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

}

void Game::ProcessInput(float dt) {

    if (this->Keys[GLFW_KEY_J]) {
        camera->SetZoom(camera->zoom - 0.003f);
    } else if (this->Keys[GLFW_KEY_K]) {
        camera->SetZoom(camera->zoom + 0.003f);
    }

    bool moved = false;
    if (this->Keys[GLFW_KEY_LEFT]) {
        player->move(LEFT);
        if (!CheckCollisions()) {
            moved = true;
        } else {
            player->move(RIGHT);
        }
    }
    if (this->Keys[GLFW_KEY_RIGHT]) {
        player->move(RIGHT);
        if (!CheckCollisions()) {
            moved = true;
        } else {
            player->move(LEFT);
        }
    }
    if (this->Keys[GLFW_KEY_UP]) {
        player->move(UP);
        if (!CheckCollisions()) {
            moved = true;
        } else {
            player->move(DOWN);
        }
    }
    if (this->Keys[GLFW_KEY_DOWN]) {
        player->move(DOWN);
        if (!CheckCollisions()) {
            moved = true;
        } else {
            player->move(UP);
        }
    }
    if (!moved) {
        player->stop();
    }
}

void Game::Render() {
    player->draw();
    for (auto x: maze->tiles) {
        Renderer->DrawSprite(x);
    }
    Renderer->DrawSprite(player);
//    Renderer->DrawSprite(tile);
//    Renderer->DrawSprite(tile2);

}

bool Game::CheckCollisions() {

    bool collided = false;

    auto playerPos = player->hitboxPos;
    auto playerSize = player->hitboxSize;
    for (auto tl : maze->tiles) {

        if (tl->isWall) {
            auto tilePos = tl->transformation.position;
            auto tileSize = tl->transformation.scale;

            bool collisionX = (playerPos.x + playerSize.x >= tilePos.x &&
                               tilePos.x + tileSize.x >= playerPos.x);
            // collision y-axis?
            bool collisionY = (playerPos.y + playerSize.y >= tilePos.y &&
                               tilePos.y + tileSize.y >= playerPos.y);
            // collision only if on both axes
            collided |= (collisionX && collisionY);
            if (collided) {
                cout << tilePos.x << " " << tilePos.y << "\n";
            }
        }
    }
    return collided;

}
