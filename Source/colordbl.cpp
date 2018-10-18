//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/colordbl.h"

colordbl::colordbl()
{
    color = glm::vec3(0.0, 0.0, 0.0);
}

colordbl::colordbl(float R, float G, float B)
{
    color = glm::vec3(R, G, B);
}

colordbl::colordbl(glm::vec3 c)
{
    color = c;
}

const float& colordbl::operator[](int i)
{
    return color[i];
}

std::ostream& operator<<(std::ostream& os, const colordbl& obj)
{
    os << "(" << obj.color.x << ", " << obj.color.y << ", " << obj.color.z << ")";
    return os;
}