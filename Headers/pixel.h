#pragma once

#include "ray.h"

class pixel {

public:
    pixel();
    pixel(ray r);
    pixel(ray rs[]);
    static const int numOfRays = 4;
    ray& getrays(int index);
    void setcolor(colordbl pixelColor);
    colordbl getColor();

private:
    colordbl p_color;
    ray rays[numOfRays];


};

