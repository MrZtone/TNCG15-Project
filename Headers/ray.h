
#ifndef PROJECT_RAY_H
#define PROJECT_RAY_H

#include "vertex.h"
#include "colordbl.h"

//TODO: Add reference to the intersection triangle


class ray {

private:
    vertex start, end;

public:
    ray();
    ray(vertex S, vertex E);
    vertex startPoint();
    vertex endPoint();
    vertex getPointOnRay(float t);

};


#endif //PROJECT_RAY_H
