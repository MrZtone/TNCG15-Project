//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/ray.h"

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