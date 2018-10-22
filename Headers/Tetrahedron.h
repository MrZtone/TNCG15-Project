#pragma once

#include "vertex.h"
#include "Shape.h"

class Tetrahedron: public Shape {

private:

    vertex point1, point2, point3, point4;

public:

    Tetrahedron();
    Tetrahedron(glm::vec4 P1,glm::vec4 P2, glm::vec4 P3, glm::vec4 P4 );
    vertex intersect(ray& arg);

};
