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

vertex ray::getPointOnRay(float t)
{
    std::cout << "beep boop I'm a ray" << std::endl;
    return vertex(start.coordinates + t*(end.coordinates-start.coordinates));
}