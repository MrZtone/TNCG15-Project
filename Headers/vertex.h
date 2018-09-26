
#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include "../glm/vec4.hpp"

class vertex
{
private:
    glm::vec4 coordinates;

public:

    vertex();
    vertex(double X, double Y, double Z, double W);
};

#endif //PROJECT_VERTEX_H
