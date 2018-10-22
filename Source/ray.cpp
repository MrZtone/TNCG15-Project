//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/ray.h"
#include "../Headers/scene.h"
#include "../Headers/Sphere.h"

#include <iostream>

ray::ray()
{
    start =vertex();
    end = vertex();
}

ray::ray(vertex S, vertex E)
{
    start=S;
    end=E;
}

vertex ray::startPoint()
{
    return start;
}

vertex ray::endPoint()
{
    return end;
}

glm::vec4 ray::getPointOnRay(float t)
{
    glm::vec4 temp = start.coordinates + t*(end.coordinates-start.coordinates);
    temp[3] = 1.0f;

    return temp;
}

float ray::getCosine(vertex& vert)
{
    glm::mat4 M = glm::inverse(toWorldCoordinates(vert));
    glm::vec3 outgoing = glm::normalize(glm::vec3(end.coordinates) - glm::vec3(start.coordinates));
    glm::vec3 normal = glm::vec3(vert.v_normal->vectorCoordinates);

    //std::cout << outgoing.x << " " << outgoing.y << " " << outgoing.z << std::endl;
    //std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;

    glm::vec4 outgoingRay = M* glm::vec4(outgoing, 1.0f);
    return glm::dot(glm::vec3(outgoingRay), glm::vec3(vert.v_normal->vectorCoordinates));

}

glm::mat4 ray::toWorldCoordinates(vertex& v)
{
    glm::vec3 Z = glm::normalize(v.v_normal->vectorCoordinates);
    glm::vec3 I = glm::vec3(start.coordinates) - glm::vec3(end.coordinates);
    glm::vec3 X = glm::normalize(I - (glm::dot(I,Z)*Z));
    glm::vec3 Y = (glm::cross(-X,Z));

    glm::mat4 M1(1.0f);
    glm::mat4 M2(1.0f);
    M1[0][0] = X.x;
    M1[1][0] = X.y;
    M1[2][0] = X.z;
    M1[0][1] = Y.x;
    M1[1][1] = Y.y;
    M1[2][1] = Y.z;
    M1[0][2] = Z.x;
    M1[1][2] = Z.y;
    M1[2][2] = Z.z;

    M2[0][3] = -v.coordinates.x;
    M2[1][3] = -v.coordinates.y;
    M2[2][3] = -v.coordinates.z;

    return glm::inverse(M1*M2);
}
