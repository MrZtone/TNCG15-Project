//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/ray.h"
#include <iostream>

ray::ray()
{
    start =vertex();
    end = vertex();
}

ray::ray(vertex S, vertex E)
{
    start=S;
    end=E;
}

vertex ray::startPoint()
{
    return start;
}

vertex ray::endPoint()
{
    return end;
}

glm::vec4 ray::getPointOnRay(float t)
{
    glm::vec4 temp = start.coordinates + t*(end.coordinates-start.coordinates);
    temp[3] = 1.0f;

    return temp;
}