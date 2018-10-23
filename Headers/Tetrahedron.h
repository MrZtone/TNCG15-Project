#pragma once

#include "vertex.h"
#include "Shape.h"
#include "triangle.h"

class Tetrahedron: public Shape {
private:

    vertex point1, point2, point3, point4, tetra_center;
    triangle tetra_faces[4];
    const float tetra_offset = 1.5f;

public:

    Tetrahedron();
    Tetrahedron(vertex tCenter);
    vertex intersect(ray& arg);

};
