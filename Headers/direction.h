//
// Created by Ola Steen on 2018-09-12.
//

#ifndef PROJECT_DIRECTION_H
#define PROJECT_DIRECTION_H

#endif //PROJECT_DIRECTION_H

#include "../glm/vec3.hpp"

class direction
{
    friend class triangle;
    friend class camera;
    friend class vertex;

private:
    glm::vec3 vectorCoordinates;

public:
    direction();
    direction(double X, double Y, double Z);
    direction(glm::vec3 vC);
    ~direction();
};