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
#include "Imposter.h"


// Game-related State data
//#3C4A4A -> 60,74,74
SpriteRenderer *Renderer;
SpriteRenderer *SkewRenderer;
Camera2D *camera;
Player *player;
Imposter *imp;
Maze *maze;
Tile *tile, *tile2, *tile3;


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
    loadImposter();
    loadTiles();

    player = new Player();
    imp = new Imposter();
    maze = new Maze();
    camera = new Camera2D(player->getPosition());
    tile = new Tile("grass-tile", imp->hitboxPos, imp->hitboxSize, false);
    tile2 = new Tile("brick-tile", maze->tiles[0]->hitboxPos, maze->tiles[0]->hitboxSize, false);
    tile3 = new Tile("brick-tile", maze->tiles[0 + maze->N + 1]->hitboxPos, maze->tiles[0 + maze->N + 1]->hitboxSize,
                     false);
    SetProjection();
    SetImposterPosition();
}


void Game::Update(float dt) {
    SetProjection();
    tile->transformation.position = imp->hitboxPos;
    tile->transformation.scale = imp->hitboxSize;
    moveImposter();
}

void Game::SetImposterPosition() {
    auto x = maze->getImposterPos();
    imp->setCenter(x);
    imp->target = x;
}

void Game::SetProjection() {
    glm::mat4 projection = camera->GetProjection(player->transformation.position);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

}

void Game::moveImposter() {
    if (imp->checkTarget()) {
        char dir = maze->runDjkstra(player->getCenter(), imp->getCenter());
        cout << dir << "\n";
        if (dir == 'U') {
            imp->target += glm::vec2(0, -TILE_SIZE.y);
        } else if (dir == 'D') {
            imp->target += glm::vec2(0, TILE_SIZE.y);
        } else if (dir == 'R') {
            imp->target += glm::vec2(TILE_SIZE.x, 0);
        } else if (dir == 'L') {
            imp->target += glm::vec2(-TILE_SIZE.x, 0);
        }
    }
    imp->move();
}


bool Game::movePlayer(MovementType dir, MovementType oppDir) {

    player->move(dir);
    auto oldAnim = player->currAnim;
    if (dir == DOWN or dir == UP) {
        player->currAnim = (oldAnim == IdleRight or oldAnim == RunRight) ? RunRight : RunLeft;
    }
    if (dir == LEFT) {
        player->currAnim = RunLeft;
    }
    if (dir == RIGHT) {
        player->currAnim = RunRight;
    }

//    if (oldAnim != player->currAnim) player->stopAnimation(oldAnim);

    if (!CheckCollisions(player)) {
        return true;
    }
    player->move(oppDir);
    return true;
}


void Game::Render() {
    player->draw();
    imp->draw();
    for (auto x: maze->tiles) {
        if ((x->isWall and x->getPosition().y < player->getPosition().y) or !x->isWall)
            Renderer->DrawSprite(x);
    }
    Renderer->DrawSprite(player);
    Renderer->DrawSprite(imp);
    for (auto x: maze->tiles) {
        if (x->isWall and x->getPosition().y >= player->getPosition().y)
            Renderer->DrawSprite(x);
    }
//    cout << "All Rendered" << "\n";
//    Renderer->DrawSprite(tile);
//    Renderer->DrawSprite(tile2);
//    Renderer->DrawSprite(tile3);

}


void Game::ProcessInput(float dt) {

    if (this->Keys[GLFW_KEY_J]) {
        camera->SetZoom(camera->zoom - 0.008f);
    } else if (this->Keys[GLFW_KEY_K]) {
        camera->SetZoom(camera->zoom + 0.008f);
    }

    bool moved = false;
    if (this->Keys[GLFW_KEY_LEFT]) {
        moved = movePlayer(LEFT, RIGHT);
    }
    if (this->Keys[GLFW_KEY_RIGHT]) {
        moved = movePlayer(RIGHT, LEFT);
    }
    if (this->Keys[GLFW_KEY_UP]) {
        moved = movePlayer(UP, DOWN);
    }
    if (this->Keys[GLFW_KEY_DOWN]) {
        moved = movePlayer(DOWN, UP);
    }
    if (!moved) {
        player->stop();
    }
}

bool Game::CheckCollisions(AnimatedSprite *sprite) {

    bool collided = false;

    auto playerPos = sprite->hitboxPos;
    auto playerSize = sprite->hitboxSize;
    for (auto tl : maze->tiles) {

        if (tl->isWall) {
            auto tilePos = tl->hitboxPos;
            auto tileSize = tl->hitboxSize;

            bool collisionX = (playerPos.x + playerSize.x >= tilePos.x && tilePos.x + tileSize.x >= playerPos.x);
            bool collisionY = (playerPos.y + playerSize.y >= tilePos.y && tilePos.y + tileSize.y >= playerPos.y);
            collided |= (collisionX && collisionY);
            if (collided) {
//                cout << tilePos.x << " " << tilePos.y << "\n";
            }
        }
    }
    return collided;

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

void Game::loadImposter() {
    for (int i = 0; i < 15; i++) {
        std::string fileR, fileL, nameL, nameR;
        fileL = "../assets/sprites/imp2/run-left/tile0";
        fileR = "../assets/sprites/imp2/run-right/tile0";
        fileL = fileL.append(i < 10 ? "0" : "") + std::to_string(i) + ".png";
        fileR = fileR.append(i < 10 ? "0" : "") + std::to_string(i) + ".png";

        nameL = "imposter-left_";
        nameR = "imposter-right_";
        nameL = nameL.append(i < 10 ? "0" : "") + std::to_string(i);
        nameR = nameR.append(i < 10 ? "0" : "") + std::to_string(i);

        ResourceManager::LoadTexture(fileL, true, nameL);
        ResourceManager::LoadTexture(fileR, true, nameR);
    }

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
