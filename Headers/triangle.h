#pragma once
#include "ray.h"


//TODO: make a proper constructor


class triangle {
    friend class camera;
    friend class lightsource;

private:

    vertex t_vertices[3];
    colordbl t_color;
    direction t_normal;

public:
    triangle();
    triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, colordbl color, direction norm, int s);
    vertex rayIntersection(ray arg);
    colordbl getColor();

};
