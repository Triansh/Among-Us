#include "Player.h"
#include <algorithm>

Player::Player() : AnimatedSprite("player-right-idle", glm::vec2(200.f, 0.f), 3.80f * glm::vec2(30, 40)) {

    vector<string> runRightAnimNames, runLeftAnimNames;
    vector<string> idleRightAnimNames = {"player-right-idle"};
    vector<string> idleLeftAnimNames = {"player-left-idle"};
    for (int i = 0; i < 24; i++) {
        string Rname = "player-right_", Lname = "player-left_";
        Lname = Lname.append(i < 10 ? "0" : "") + std::to_string(i);
        Rname = Rname.append(i < 10 ? "0" : "") + std::to_string(i);
        runLeftAnimNames.push_back(Lname);
        runRightAnimNames.push_back(Rname);
    }
    reverse(runRightAnimNames.begin(), runRightAnimNames.end());

    auto *runLeftAnimation = new Animation2D(40, runLeftAnimNames);
    auto *runRightAnimation = new Animation2D(40, runRightAnimNames);
    auto *idleLeftAnimation = new Animation2D(1, idleLeftAnimNames);
    auto *idleRightAnimation = new Animation2D(1, idleRightAnimNames);
    addAnimation(RunLeft, runLeftAnimation);
    addAnimation(RunRight, runRightAnimation);
    addAnimation(IdleLeft, idleLeftAnimation);
    addAnimation(IdleRight, idleRightAnimation);
    this->speed = 8.0f;
    setHitbox();
}

void Player::move(MovementType mt) {
    if (mt == RIGHT) {
        addPosition(glm::vec2(speed, 0.0f));
    }
    if (mt == LEFT) {
        addPosition(glm::vec2(-speed, 0.0f));
    }
    if (mt == UP) {
        addPosition(glm::vec2(0.0f, -speed));
    }
    if (mt == DOWN) {
        addPosition(glm::vec2(0.0f, speed));
    }
    setHitbox();
}

void Player::setHitbox() {
    hitboxPos = glm::vec2(transformation.position.x + 30,
                          transformation.position.y + transformation.scale.y - 55);
    hitboxSize = glm::vec2(transformation.scale.x - 60, 14 + 5);
}

void Player::stop() {
    currAnim = (currAnim == IdleRight or currAnim == RunRight) ? IdleRight : IdleLeft;;
}



