#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include "Shape.h"
#include "../glm/gtx/intersect.hpp"

class Sphere: public Shape {


private:
    vertex sphere_center;
    float radius;
    float t;
    colordbl s_color;

public:

    Sphere();
    Sphere(vertex POSITION, float RADIUS, colordbl c = colordbl(1.0, 1.0, 1.0));
    vertex intersect(ray& arg);
    void set_t(float T);


};
