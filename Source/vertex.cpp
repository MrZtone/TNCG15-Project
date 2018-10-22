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
vertex::vertex(const vertex& v)
{
    coordinates =v.coordinates;
    v_color = v.v_color;
    surface = v.surface;
    storesNormal = v.storesNormal;
    if(v.storesNormal)
        v_normal = new direction(v.v_normal->vectorCoordinates);
    else
        v_normal=v.v_normal;
}
vertex::~vertex()
{
    if (storesNormal && v_normal != nullptr)
    {
        delete v_normal;
        v_normal = nullptr;
    }
}

glm::vec3 vertex::operator -(vertex& arg1){

    return glm::vec3(arg1.coordinates - coordinates);
}

bool operator!=(const vertex& X, const vertex& Y)
{
    return (X.coordinates != Y.coordinates);
}

float vertex::distance(vertex& v)
{
    return glm::length(glm::vec3(coordinates - v.coordinates));
}
