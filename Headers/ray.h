//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_RAY_H
#define PROJECT_RAY_H

#include "vertex.h"

//TODO: Add refrence to the intersection triangle


class ray {

private:
    vertex start, end;

public:
    ray();
    ray(vertex S, vertex E);

};


#endif //PROJECT_RAY_H
