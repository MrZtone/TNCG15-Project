//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/vertex.h"


vertex::vertex()
{
    coordinates = glm::vec4(0.0, 0.0, 0.0, 0.0);
}

vertex::vertex(double X, double Y, double Z, double W)
{
    coordinates = glm::vec4(X, Y, Z, W);
}