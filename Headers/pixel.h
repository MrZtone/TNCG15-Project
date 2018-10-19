//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_PIXEL_H
#define PROJECT_PIXEL_H

#include "ray.h"

class pixel {

public:
    pixel();
    pixel(ray r);
    static const int numOfRays = 1;
    ray& getrays(int index);
    void setcolor(colordbl pixelColor);
    colordbl getColor();

private:
    colordbl p_color;
    ray rays[numOfRays];


};


#endif //PROJECT_PIXEL_H
