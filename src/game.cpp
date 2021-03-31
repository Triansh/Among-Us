#include <iostream>
#include <cstdlib>
#include <sstream>
#include "game.h"
#include "resourceManager.h"
#include "spriteRenderer.h"
#include "Camera2D.h"
#include "Imposter.h"
#include "PowerUp.h"
#include "textRenderer.h"

SpriteRenderer *Renderer;
Camera2D *camera;
Player *player;
Imposter *imp;
Maze *maze;
Tile *youWin, *youLose;
Tile *endTile, *startTile;
PowerUp *killImposter, *addObstacles;
TextRenderer *Text;

Game::Game(unsigned int width, unsigned int height)
        : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {
    index = 0;
}

Game::~Game() {
    delete Renderer;
    delete camera;
    delete player;
    delete imp;
    delete maze;
    delete youWin;
    delete youLose;
}

void Game::Init() {

    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("../assets/fonts/Hack-Bold.ttf", 24);

    // load shaders
    ResourceManager::LoadShader("../src/shaders/sprite.vs", "../src/shaders/sprite.fs", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection =
            glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);

    // load textures
    std::cout << "\n=====================================================================\n";
    std::cout << getenv("PWD") << "\n";
    std::cout << "\n=====================================================================\n";

    loadPlayer();
    loadImposter();
    loadTiles();

    maze = new Maze();
    player = new Player();
    imp = new Imposter();
    camera = new Camera2D(player->getPosition());

    unsigned int tileStartId = 1, tileEndId = maze->tiles.size() - 2;
    startTile = new Tile("start-tile", maze->tiles[tileStartId]->getPosition(), TILE_SIZE, false);
    endTile = new Tile("trophy-tile", maze->tiles[tileEndId]->getPosition(), TILE_SIZE, false);

    killImposter = new PowerUp("report", glm::vec2(0), TILE_SIZE, KILL_IMPOSTER);
    addObstacles = new PowerUp("powerup", glm::vec2(0), TILE_SIZE, ACTIVATE_OBS);
    killImposter->setCenter(maze->getTaskTilePosition(1));
    addObstacles->setCenter(maze->getTaskTilePosition(2));

    auto youWinSize = glm::vec2(600.0f, 600.0f), youLostSize = glm::vec2(800.0f, 400.0f);
    youWin = new Tile("you-win", glm::vec2(0.0f), youWinSize, false);
    youLose = new Tile("you-lose", glm::vec2(0.0f), youLostSize, false);

    SetProjection();
    SetImposterPosition();
}


void Game::Update() {
    SetProjection();
    moveImposter();
    switchLights(!info.lighting);

    if (CheckCollisions(player, addObstacles)) {
        if (addObstacles->activate()) {
            maze->makeObstacles();
            info.tasksCompleted += 1;
        }
    }

    if (CheckCollisions(player, killImposter)) {
        if (killImposter->activate()) {
            imp->isDead = true;
            info.tasksCompleted += 1;
        }
    }

    for (auto &obs : maze->obstacles) {
        if (CheckCollisions(player, obs)) {
            if (obs->activate()) {
                if (obs->type == COIN) {
                    info.score += 50;
                } else {
                    info.score -= 60;
                }
            }
        }
    }

    if (CheckCollisions(player, endTile) and info.tasksCompleted == 2) {
        State = GAME_WIN;
    }

    if (glfwGetTime() > info.clock or (!imp->isDead and CheckCollisions(player, imp))) {
        State = GAME_LOST;
    }

    info.score += (!info.lighting ? 2.0f : 1.0f) / FPS;
}

void Game::Render() {

    if (State == GAME_ACTIVE) {

        player->draw();
        imp->draw();

        for (auto x: maze->tiles) {
            if ((x->isWall and x->getPosition().y < player->getPosition().y) or !x->isWall)
                Renderer->DrawSprite(x);
        }

        if (checkInsideLightArea(startTile->getCenter()))Renderer->DrawSprite(startTile);
        if (checkInsideLightArea(endTile->getCenter()) and info.tasksCompleted == 2) Renderer->DrawSprite(endTile);

        if (!killImposter->isActive and checkInsideLightArea(killImposter->getCenter()))
            Renderer->DrawSprite(killImposter);
        if (!addObstacles->isActive and checkInsideLightArea(addObstacles->getCenter()))
            Renderer->DrawSprite(addObstacles);

        for (auto x : maze->obstacles) {
            if (!x->isActive and checkInsideLightArea(x->getCenter())) Renderer->DrawSprite(x);
        }

        Renderer->DrawSprite(player);
        if (!imp->isDead and checkInsideLightArea(imp->getCenter())) Renderer->DrawSprite(imp);

        for (auto x: maze->tiles) {
            if (x->isWall and x->getPosition().y >= player->getPosition().y)
                Renderer->DrawSprite(x);
        }
        renderHUD();

    } else {
        clearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        auto screenCenter =
                glm::vec2(camera->left, camera->top) + glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT) / 2.0f / camera->zoom;
        if (State == GAME_WIN) {
            youWin->setCenter(screenCenter);
            Renderer->DrawSprite(youWin);
        } else if (State == GAME_LOST) {
            youLose->setCenter(screenCenter);
            Renderer->DrawSprite(youLose);
        }
    }

}

void Game::renderHUD() const {
    std::stringstream score, time, light, tasks;
    time << info.clock - (int) glfwGetTime();
    score << (int) info.score;
    tasks << info.tasksCompleted;
    light << (info.lighting ? "ON" : "OFF");

    float factor = 1.0f / camera->zoom;
    float hudTop = camera->top + 10 * factor, hupLeft = camera->right - 200 * factor;
    Text->RenderText("SCORE: " + score.str(), hupLeft, hudTop, factor);
    Text->RenderText("TASKS: " + tasks.str() + " / 2", hupLeft, hudTop + 30 * factor, factor);
    Text->RenderText("LIGHT: " + light.str(), hupLeft, hudTop + 30 * 2 * factor, factor);
    Text->RenderText("TIME: " + time.str(), hupLeft, hudTop + 30 * 3 * factor, factor);

}

void Game::switchLights(bool lightOff) {
    auto color = glm::vec3(1.0f, 1.0f, 1.0f);
    auto colorOff = color * 0.3f;

    for (auto &x : maze->tiles) {
        x->setColor(lightOff ? colorOff : color);
    }

    auto pos = player->getCenter() + glm::vec2(0.0f, 25.f);
    info.lightArea = maze->changeColor(pos, color);
}

bool Game::checkInsideLightArea(glm::vec2 pos) const {

    if (info.lighting) return true;

    auto minx = info.lightArea.x, miny = info.lightArea.y;
    auto maxx = info.lightArea.z, maxy = info.lightArea.w;

    return (pos.x >= minx and pos.x <= maxx and pos.y >= miny and pos.y <= maxy);
}

void Game::ProcessInput() {

    if (State == GAME_ACTIVE) {

        if (this->Keys[GLFW_KEY_L]) {
            info.lighting = !info.lighting;
            Keys[GLFW_KEY_L] = false;
        }

        float cameraFactor = 0.005f;
        if (this->Keys[GLFW_KEY_J]) {
            camera->SetZoom(camera->zoom - cameraFactor);
        } else if (this->Keys[GLFW_KEY_K]) {
            camera->SetZoom(camera->zoom + cameraFactor);
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

    if (player->getPosition().y < 0 or
        player->getPosition().y + player->getSize().y >= (2 * MAZE_HEIGHT + 1) * TILE_SIZE.y) {
        player->move(oppDir);
        return false;
    }

    if (!CheckTileCollisions(player)) {
        return true;
    }

    player->move(oppDir);

    return true;
}

void Game::moveImposter() {
    if (imp->checkTarget()) {
        char dir = maze->runDjkstra(player->getCenter(), imp->getCenter());
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

void Game::SetImposterPosition() {
    auto x = maze->getImposterPos();
    imp->setCenter(x);
    imp->target = x;
}

void Game::SetProjection() {
    glm::mat4 projection = camera->GetProjection(player->transformation.position);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection, true);
    ResourceManager::GetShader("text").SetMatrix4("projection", projection, true);
}

void Game::clearColor(glm::vec4 color) {
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Game::CheckCollisions(Sprite *sprite, Sprite *collider) {

    auto spritePos = sprite->hitboxPos, spriteSize = sprite->hitboxSize;
    auto colliderPos = collider->hitboxPos, colliderSize = collider->hitboxSize;

    bool collisionX = (spritePos.x + spriteSize.x >= colliderPos.x && colliderPos.x + colliderSize.x >= spritePos.x);
    bool collisionY = (spritePos.y + spriteSize.y >= colliderPos.y && colliderPos.y + colliderSize.y >= spritePos.y);
    return (collisionX & collisionY);
}

bool Game::CheckTileCollisions(Sprite *sprite) {
    bool collided = false;
    for (auto tl : maze->tiles) {
        if (tl->isWall) {
            collided |= CheckCollisions(sprite, tl);
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
        fileL = "../assets/sprites/imposter/run-left/tile0";
        fileR = "../assets/sprites/imposter/run-right/tile0";
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
    ResourceManager::LoadTexture("../assets/tiles/skeld-wall.png", true, "skeld-wall");
    ResourceManager::LoadTexture("../assets/tiles/start-tile.png", true, "start-tile");
    ResourceManager::LoadTexture("../assets/tiles/trophy-tile.png", true, "trophy-tile");

    ResourceManager::LoadTexture("../assets/miscellaneous/report.png", true, "report");
    ResourceManager::LoadTexture("../assets/miscellaneous/powerup.png", true, "powerup");
    ResourceManager::LoadTexture("../assets/miscellaneous/coin.png", true, "coin");
    ResourceManager::LoadTexture("../assets/miscellaneous/bomb.png", true, "bomb");
    ResourceManager::LoadTexture("../assets/miscellaneous/you-win.png", true, "you-win");
    ResourceManager::LoadTexture("../assets/miscellaneous/you-lost.png", true, "you-lose");
}