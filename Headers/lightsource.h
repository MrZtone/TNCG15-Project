#pragma once

#include "scene.h"
#include "Sphere.h"
#include "../glm/glm.hpp"


class lightsource {

private:
    triangle l_surface;
    float pointRaddiace;

public:
    static const int numOfSamples= 10;
    lightsource();
    float calclight(vertex& vert, scene& sc, Sphere& s);
    vertex findClosestIntersection(ray& r, scene& sc, Sphere& s);

};
