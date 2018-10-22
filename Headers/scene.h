//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include "triangle.h"
#include "Shape.h"


class scene: public Shape {

public:
    static const int SIZE = 24;
    scene();
    triangle& getWallTriangle(int index);
    vertex intersect(ray& arg);

private:
     triangle walls[SIZE];

};


#endif //PROJECT_SCENE_H
