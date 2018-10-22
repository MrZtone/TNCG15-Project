#pragma once

#include "vertex.h"
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