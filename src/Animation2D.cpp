//
// Created by triansh on 24/03/21.
//

#include <GLFW/glfw3.h>
#include "Animation2D.h"

Animation2D::Animation2D(float fps, vector<string> &textures) {
    currentIndex = 0;
    this->fps = fps;
    this->textures = textures;
    deltaTime = 1.0 / fps;
    lastFrame = 0;
}

void Animation2D::play() {

    double cur_frame = glfwGetTime();
    if (cur_frame - lastFrame > deltaTime) {
        currentIndex = (currentIndex + 1) % textures.size();
        lastFrame = cur_frame;
    }
}

string Animation2D::getAnimation() {
    return textures[currentIndex];
}

void Animation2D::stop() {
    currentIndex = 0;
    lastFrame = 0;
}
