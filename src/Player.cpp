#include "Player.h"
#include <algorithm>

Player::Player() : Sprite("sprite_24", glm::vec2(200, -50), 4.0f * glm::vec2(30, 40)) {

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

    auto *runLeftAnimation = new Animation2D(48, runLeftAnimNames);
    auto *runRightAnimation = new Animation2D(48, runRightAnimNames);
    auto *idleLeftAnimation = new Animation2D(1, idleLeftAnimNames);
    auto *idleRightAnimation = new Animation2D(1, idleRightAnimNames);
    addAnimation(RunLeft, runLeftAnimation);
    addAnimation(RunRight, runRightAnimation);
    addAnimation(IdleLeft, idleLeftAnimation);
    addAnimation(IdleRight, idleRightAnimation);
    this->speed = 5.0f;

    setHitboxes();
}

void Player::move(MovementType mt) {

    if (mt == RIGHT) {
        addPosition(glm::vec2(speed, 0.0f));
        currAnim = RunRight;
    }
    if (mt == LEFT) {
        addPosition(glm::vec2(-speed, 0.0f));
        currAnim = RunLeft;
    }
    if (mt == UP) {
        addPosition(glm::vec2(0.0f, -speed));
        currAnim = (currAnim == IdleRight or currAnim == RunRight) ? RunRight : RunLeft;
    }
    if (mt == DOWN) {
        addPosition(glm::vec2(0.0f, speed));
        currAnim = (currAnim == IdleRight or currAnim == RunRight) ? RunRight : RunLeft;
    }
    setHitboxes();
}

void Player::setHitboxes() {
    hitboxPos = glm::vec2(transformation.position.x + 30,
                          transformation.position.y + transformation.scale.y - 40);
    hitboxSize = glm::vec2(transformation.scale.x - 60, 25);
}

void Player::stop() {
    currAnim = (currAnim == IdleRight or currAnim == RunRight) ? IdleRight : IdleLeft;;
}


