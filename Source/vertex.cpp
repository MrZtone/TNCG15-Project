//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/vertex.h"



//constructors
vertex::vertex()
{
    coordinates = glm::vec4(0.0, 0.0, 0.0, 0.0);
    v_color = nullptr;
    v_normal = nullptr;
    surface= -1;
    storesNormal =false;
}

vertex::vertex(double X, double Y, double Z, double W, colordbl* c, direction* n, int s, bool sN)
{
    coordinates = glm::vec4(X, Y, Z, W);
    v_color = c;
    v_normal = n;
    surface = s;
    storesNormal =sN;
}

vertex::vertex(glm::vec4 cor, colordbl* col , direction* n, int s, bool sN)
{
    coordinates = cor;
    v_color = col;
    v_normal = n;
    surface = s;
    storesNormal =sN;
}
vertex::~vertex()
{
    if (storesNormal)
        delete v_normal;
}

glm::vec3 vertex::operator -(vertex& arg1){

    return glm::vec3(arg1.coordinates - coordinates);
}

bool operator!=(const vertex& X, const vertex& Y)
{
    return (X.coordinates != Y.coordinates);
}
