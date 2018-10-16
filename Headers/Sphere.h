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

public:

    Sphere();
    Sphere(vertex POSITION, float RADIUS);
    vertex sphereIntersect(ray& arg);
    void set_t(float T);


};


#endif //PROJECT_SPHERE_H
