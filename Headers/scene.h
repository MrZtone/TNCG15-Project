//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_SCENE_H
#define PROJECT_SCENE_H

#include "triangle.h"


class scene {

private:
    vertex s_vertices[24];

public:

    scene();
    triangle rayIntersection(ray arg);
};


#endif //PROJECT_SCENE_H
