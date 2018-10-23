#pragma once
#include "../glm/glm.hpp"

class direction
{
    friend class triangle;
    friend class camera;
    friend class vertex;
    friend class ray;
    friend class lightsource;

private:
    glm::vec3 vectorCoordinates;

public:
    direction();
    direction(double X, double Y, double Z);
    direction(glm::vec3 vC);
    ~direction();
};
