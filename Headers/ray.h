
#ifndef PROJECT_RAY_H
#define PROJECT_RAY_H

#include "vertex.h"
#include "colordbl.cpp"

//TODO: Add reference to the intersection triangle


class ray {

private:
    vertex start, end;

public:
    ray();
    ray(vertex S, vertex E);

};


#endif //PROJECT_RAY_H
