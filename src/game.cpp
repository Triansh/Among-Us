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


// Game-related State data
SpriteRenderer *Renderer;


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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load textures
    std::cout << "\n=====================================================================\n";
    std::cout << getenv("PWD") << "\n";
    std::cout << "\n=====================================================================\n";


//    vector<string> animNames;
    for (int i = 0; i < 24; i++) {
        std::string file, name;
        file = "../assets/sprites/run/tile0";
        file = file.append(i < 10 ? "0" : "") + std::to_string(i) + ".png";
        name = "sprite_";
        name = name.append(i < 10 ? "0" : "") + std::to_string(i);
        std::cout << name << " " << file << "\n";
//        animNames.push_back(name);
        ResourceManager::LoadTexture(file, true, name);
    }
    std::string s = "../assets/sprites/standleft.png";
    ResourceManager::LoadTexture(s, true, "sprite_24");

    player = new Player();
//    sp = new Sprite("sprite_24", glm::vec2(200, 200), 5.0f * glm::vec2(30, 40));
//    auto *animation = new Animation2D(48, animNames);
//    sp->addAnimation(Run, animation);

}

void Game::Update(float dt) {

}

void Game::ProcessInput(float dt) {
    bool moved = false;
    if (this->Keys[GLFW_KEY_LEFT]) {
        moved = true;
        player->move(LEFT);
    }
    if (this->Keys[GLFW_KEY_RIGHT]) {
        moved = true;
        player->move(RIGHT);
    }
    if (this->Keys[GLFW_KEY_UP]) {
        moved = true;
        player->move(UP);
    }
    if (this->Keys[GLFW_KEY_DOWN]) {
        moved = true;
        player->move(DOWN);
    }
    if (!moved) {
        player->stop();
    }
}

void Game::Render() {
//    std::string name = "sprite_";
//    name = name.append(index / 2 < 10 ? "0" : "") + std::to_string(index / 2);
//    Texture2D texture = ResourceManager::GetTexture(name);
    player->draw();
    Renderer->DrawSprite(player->sprite);
    index = (index + 1) % 48;
}