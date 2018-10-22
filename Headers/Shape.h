
#include "../glm/vec3.hpp"

#ifndef PROJECT_SHAPE_H
#define PROJECT_SHAPE_H

#include "vertex.h"
#include "ray.h"

enum MaterialType { DIFFUSE,DIFFUSE_AND_GLOSSY, REFLECTION_AND_REFRACTION, REFLECTION };

class Shape {

private:

protected:
    glm::vec3 diffuseColor;
    float specularExponent;
    MaterialType materialType;

public:
    Shape();
    virtual ~Shape();
    virtual vertex intersect(ray& arg)  = 0;
};

#endif //PROJECT_SHAPE_H