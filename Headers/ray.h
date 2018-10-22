#pragma once

#include "vertex.h"



//TODO: Add reference to the intersection triangle


class ray {
    friend class camera;

private:
    vertex start, end;

public:
    ray();
    ray(vertex S, vertex E);
    vertex startPoint();
    vertex endPoint();
    glm::vec4 getPointOnRay(float t);
    float getCosine(vertex& vert);
    glm::mat4 toWorldCoordinates(vertex& v);

};