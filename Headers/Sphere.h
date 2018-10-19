#include "Shape.h"
#include "triangle.h"
#include "ray.h"

#ifndef PROJECT_SPHERE_H
#define PROJECT_SPHERE_H


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


#endif //PROJECT_SPHERE_H
