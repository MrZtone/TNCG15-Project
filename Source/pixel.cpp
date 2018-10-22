//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/pixel.h"

pixel::pixel()
{
    rays[0] = ray(vertex(), vertex());
}

pixel::pixel(ray r) {
    rays[0] = r;
}

pixel::pixel(ray rs[])
{
    for(int i =0; i < numOfRays; ++i)
    {
        rays[i] = rs[i];
    }
}

ray& pixel::getrays(int index)
{
    return rays[index];
}

void pixel::setcolor(colordbl pixelColor)
{
    p_color = pixelColor;
}

colordbl pixel::getColor()
{
    return p_color;
}