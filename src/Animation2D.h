//
// Created by triansh on 24/03/21.
//

#ifndef AMONGUS_ANIMATION2D_H
#define AMONGUS_ANIMATION2D_H


#include<iostream>
#include <vector>
using namespace std;


class Animation2D {

public:
    unsigned int current_index;
    float fps;

    vector<string> textures;

    Animation2D(float fps, vector<string> &textures);

    void play();

    string getAnimation();

private:
    double deltaTime;
    double lastFrame;

};


#endif //AMONGUS_ANIMATION2D_H
