//
// Created by triansh on 24/03/21.
//

#include "Player.h"


Player::Player(float speed) {

    vector<string> runAnimNames;
    vector<string> idleAnimNames = {"sprite_24"};
    for (int i = 0; i < 24; i++) {
        string name = "sprite_";
        name = name.append(i < 10 ? "0" : "") + std::to_string(i);
        runAnimNames.push_back(name);
    }

    sprite = new Sprite("sprite_24", glm::vec2(200, 200), 4.0f * glm::vec2(30, 40));
    auto *runAnimation = new Animation2D(48, runAnimNames);
    auto *idleAnimation = new Animation2D(1, idleAnimNames);
    sprite->addAnimation(Run, runAnimation);
    sprite->addAnimation(Idle, idleAnimation);
    this->speed = speed;

}

void Player::draw() {
    sprite->draw();

}

void Player::move(MovementType mt) {

    if (mt == RIGHT) {
        sprite->transformation.position.x += speed;
        sprite->currentAnim = Run;
        if (sprite->transformation.scale.x > 0) {
            sprite->transformation.position.x += sprite->transformation.scale.x;
            sprite->transformation.scale.x *= -1;
        }
    }
    if (mt == LEFT) {
        sprite->transformation.position.x -= speed;
        sprite->currentAnim = Run;
        if (sprite->transformation.scale.x < 0) {
            sprite->transformation.position.x += sprite->transformation.scale.x;
            sprite->transformation.scale.x *= -1;
        }
    }
    if (mt == UP) {
        sprite->transformation.position.y -= speed;
        sprite->currentAnim = Run;
    }
    if (mt == DOWN) {
        sprite->transformation.position.y += speed;
        sprite->currentAnim = Run;
    }

}

void Player::stop() {
    sprite->currentAnim = Idle;
}



