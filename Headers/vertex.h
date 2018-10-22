
#ifndef PROJECT_VERTEX_H
#define PROJECT_VERTEX_H

#include "../glm/vec4.hpp"
#include "../glm/vec3.hpp"
#include "../glm/geometric.hpp"
#include "../Headers/colordbl.h"
#include "../Headers/direction.h"


class vertex
{
    friend class triangle;
    friend class ray;
    friend class camera;
    friend class Sphere;

private:
    glm::vec4 coordinates;
    colordbl* v_color;
    direction* v_normal;
    int surface;
    bool storesNormal;

public:
    vertex();
    vertex(double X, double Y, double Z, double W, colordbl* c = nullptr, direction* n = nullptr, int s = -1, bool sN =false);
    vertex(glm::vec4 cor, colordbl* col = nullptr , direction* n = nullptr, int s = -1, bool sN =false);
    vertex(const vertex& v);
    ~vertex();
    glm::vec3 operator-(vertex& arg1);
    friend bool operator!=(const vertex& X, const vertex& Y);
    float distance(vertex& v);
    static const int DIFFUSE =1, SPECULAR =2;

};

#endif //PROJECT_VERTEX_H
