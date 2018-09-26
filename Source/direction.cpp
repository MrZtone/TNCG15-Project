//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/direction.h"

direction::direction()
{
    vectorCoordinates = glm::vec3(0.0, 0.0, 0.0);
}

direction::direction(double X, double Y, double Z)
{
    vectorCoordinates = glm::vec3(X, Y, Z);
}