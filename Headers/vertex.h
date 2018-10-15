
#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include "../glm/vec4.hpp"

class vertex
{
    friend class triangle;
    friend class ray;

private:
    glm::vec4 coordinates;

public:

    vertex();
    vertex(double X, double Y, double Z, double W);
    vertex(glm::vec4 c);

};

#endif //PROJECT_VERTEX_H
