//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_PIXEL_H
#define PROJECT_PIXEL_H


#include "colordbl.h"
#include "ray.h"

class pixel {

private:
    colordbl p_color;
    ray rays[1];

public:
    pixel();


};


#endif //PROJECT_PIXEL_H
