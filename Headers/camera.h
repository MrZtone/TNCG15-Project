
#pragma once

#include "pixel.h"
#include "ray.h"
#include "scene.h"
#include "Sphere.h"
#include "../glm/mat4x4.hpp"
#include "lightsource.h"


class camera {

public:
    static const int maxDepth = 2;

    camera();
    static const int width = 200;
    static const int height = 200;
    int intersectCounter;
    void render(scene& sc, Sphere& s, lightsource& light); //assigns value to viewplane
    void createImage(); //converts viewplane values to RGB values
    glm::mat4 toWorldCoordinates(vertex& v, ray& r);
    glm::vec3 castRay(ray& r, vertex& v, scene& sc, Sphere& s, float importance, int depth, lightsource& light);
    vertex findClosestIntersection(ray& r, scene& sc, Sphere& s, int depth);

private:
    vertex eye1, eye2;
    pixel viewplane[width][height];
};
