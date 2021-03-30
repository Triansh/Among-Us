//
// Created by triansh on 26/03/21.
//

#include "Imposter.h"
#include <algorithm>

Imposter::Imposter() : AnimatedSprite("imposter-left_00", glm::vec2(200.f, 200.f), 5.0f * glm::vec2(30, 30)) {

    vector<string> runRightAnimNames, runLeftAnimNames;
    for (int i = 0; i < 15; i++) {
        string Rname = "imposter-right_", Lname = "imposter-left_";
        Lname = Lname.append(i < 10 ? "0" : "") + std::to_string(i);
        Rname = Rname.append(i < 10 ? "0" : "") + std::to_string(i);
        runLeftAnimNames.push_back(Lname);
        runRightAnimNames.push_back(Rname);
    }

//    reverse(runLeftAnimNames.begin(), runLeftAnimNames.end());

    auto *runLeftAnimation = new Animation2D(30, runLeftAnimNames);
    auto *runRightAnimation = new Animation2D(30, runRightAnimNames);
    addAnimation(RunLeft, runLeftAnimation);
    addAnimation(RunRight, runRightAnimation);

    speed = 5.0f;
    isDead = false;
    setHitbox();

}

void Imposter::move() {

    auto oldAnim = currAnim;

    if (target.x == getCenter().x) {
        transformation.position.y += speed * (target.y < getCenter().y ? -1.0f : 1.0f);
    } else {
        transformation.position.x += speed * (target.x < getCenter().x ? -1.0f : 1.0f);
        currAnim = target.x < getCenter().x ? RunLeft : RunRight;
    }

    if (oldAnim != currAnim) stopAnimation(oldAnim);

    setHitbox();
}

void Imposter::setHitbox() {
    hitboxPos = transformation.position + glm::vec2(10, 25);
    hitboxSize = transformation.scale - glm::vec2(10, 40);
}

bool Imposter::checkTarget() {
//    cout << getCenter().x << " " << getCenter().y << " " << target.x << " " << target.y << "\n";
    return getCenter() == target;
}

