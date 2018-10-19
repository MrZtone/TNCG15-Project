
#ifndef PROJECT_TRIANGLE_H
#define PROJECT_TRIANGLE_H


#include "ray.h"


//TODO: make a proper constructor


class triangle {
    friend class camera;

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


#endif //PROJECT_TRIANGLE_H
