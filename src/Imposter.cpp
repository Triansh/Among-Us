//
// Created by triansh on 26/03/21.
//

#include "Imposter.h"
#include <algorithm>

//void Imposter::move(MovementType mt) {
//
//}

Imposter::Imposter() : AnimatedSprite("imposter-left_00", glm::vec2(200.f, 200.f), 4.0f * glm::vec2(30, 40)) {

    vector<string> runRightAnimNames, runLeftAnimNames;
    for (int i = 0; i < 37; i++) {
        string Rname = "imposter-right_", Lname = "imposter-left_";
        Lname = Lname.append(i < 10 ? "0" : "") + std::to_string(i);
        Rname = Rname.append(i < 10 ? "0" : "") + std::to_string(i);
        runLeftAnimNames.push_back(Lname);
        runRightAnimNames.push_back(Rname);
    }

    reverse(runLeftAnimNames.begin(), runLeftAnimNames.end());

    auto *runLeftAnimation = new Animation2D(12, runLeftAnimNames);
    auto *runRightAnimation = new Animation2D(12, runRightAnimNames);
    addAnimation(RunLeft, runLeftAnimation);
    addAnimation(RunRight, runRightAnimation);

}

