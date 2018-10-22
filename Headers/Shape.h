#pragma once

#include "ray.h"
#include "../glm/glm.hpp"

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