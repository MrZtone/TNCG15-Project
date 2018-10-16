
#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include "../glm/vec4.hpp"
#include "../glm/vec3.hpp"
#include "../glm/geometric.hpp"


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
    glm::vec3 operator-(vertex& arg1);
    friend bool operator!=(const vertex& X, const vertex& Y);

};

#endif //PROJECT_VERTEX_H
