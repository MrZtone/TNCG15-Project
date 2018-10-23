#pragma once

#include "scene.h"
#include "Sphere.h"
#include "../glm/glm.hpp"
#include "Tetrahedron.h"


class lightsource {

private:
    triangle l_surface;
    float pointRaddiace;

public:
    static const int numOfSamples= 25;
    lightsource();
    float calclight(vertex& vert, scene& sc, Sphere& s, Tetrahedron& tr);
    vertex findClosestIntersection(ray& r, scene& sc, Sphere& s, Tetrahedron& tr);

};
