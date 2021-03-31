#include <algorithm>
#include "Imposter.h"

Imposter::Imposter() : AnimatedSprite("imposter-left_00", glm::vec2(200.f, 200.f), 5.0f * glm::vec2(30, 30)) {

    vector<string> runRightAnimNames, runLeftAnimNames;
    for (int i = 0; i < 15; i++) {
        string Rname = "imposter-right_", Lname = "imposter-left_";
        Lname = Lname.append(i < 10 ? "0" : "") + std::to_string(i);
        Rname = Rname.append(i < 10 ? "0" : "") + std::to_string(i);
        runLeftAnimNames.push_back(Lname);
        runRightAnimNames.push_back(Rname);
    }
    reverse(runLeftAnimNames.begin(), runLeftAnimNames.end());

    auto *runLeftAnimation = new Animation2D(24, runLeftAnimNames);
    auto *runRightAnimation = new Animation2D(24, runRightAnimNames);
    addAnimation(RunLeft, runLeftAnimation);
    addAnimation(RunRight, runRightAnimation);

    speed = 5.0f;
    isDead = false;
    setHitbox();
}

void Imposter::move() {

    if (target.x == getCenter().x) {
        transformation.position.y += speed * (target.y < getCenter().y ? -1.0f : 1.0f);
    } else {
        transformation.position.x += speed * (target.x < getCenter().x ? -1.0f : 1.0f);
        currAnim = target.x < getCenter().x ? RunLeft : RunRight;
    }
    setHitbox();
}

void Imposter::setHitbox() {
    hitboxPos = transformation.position + glm::vec2(10, 25);
    hitboxSize = transformation.scale - glm::vec2(10, 40);
}

bool Imposter::checkTarget() {
    return getCenter() == target;
}

