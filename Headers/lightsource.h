//
// Created by Ola Steen on 2018-10-22.
//

#ifndef PROJECT_LIGHTSOURCE_H
#define PROJECT_LIGHTSOURCE_H

#include "triangle.h"
#include "scene.h"
#include "Sphere.h"
#include "../glm/glm.hpp""


class lightsource {

private:
    triangle l_surface;
    float pointRaddiace;

public:
    static const int numOfSamples= 6;
    lightsource();
    float calclight(vertex& vert, scene& sc, Sphere& s);

};


#endif //PROJECT_LIGHTSOURCE_H
