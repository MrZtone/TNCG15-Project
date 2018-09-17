//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_TRIANGLE_H
#define PROJECT_TRIANGLE_H

#include "vertex.h"
#include "colordbl.h"
#include "direction.h"
#include "ray.h"

//TODO: make a propper contructor


class triangle {

private:

    vertex t_vertices[3];
    colordbl t_color;
    direction t_normal;

public:
    triangle();

};


#endif //PROJECT_TRIANGLE_H
