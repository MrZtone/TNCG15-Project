//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include "triangle.h"


class scene {

public:
    static const int SIZE = 24;
    scene();
    triangle& getWallTriangle(int index);

private:
     triangle walls[SIZE];

};


#endif //PROJECT_SCENE_H
