
#include "../Headers/triangle.h"
#include "../glm/glm.hpp"
#include <iostream>

triangle::triangle()
{
}

triangle::triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, colordbl color, direction norm, int s)
{
    t_color = color;
    t_normal = norm;
    t_vertices[0] = vertex(glm::vec4(v1, 1.0f), &t_color, &t_normal, vertex::DIFFUSE);
    t_vertices[1] = vertex(glm::vec4(v2, 1.0f), &t_color, &t_normal, vertex::DIFFUSE);
    t_vertices[2] = vertex(glm::vec4(v3, 1.0f), &t_color, &t_normal, vertex::DIFFUSE);
}


vertex triangle::rayIntersection(ray arg)
{
    //Möller Trumbore algorithm
    glm::vec3 T(arg.startPoint().coordinates - t_vertices[0].coordinates);
    glm::vec3 E1(t_vertices[1].coordinates - t_vertices[0].coordinates);
    glm::vec3 E2(t_vertices[2].coordinates - t_vertices[0].coordinates);
    glm::vec3 D(arg.endPoint().coordinates - arg.startPoint().coordinates);
    glm::vec3 P = glm::cross(D, E2);
    glm::vec3 Q = glm::cross(T, E1);

    glm::vec3 Tuv= glm::vec3(glm::dot(Q,E2), glm::dot(P,T), glm::dot(Q,D)) * (1/glm::dot(P,E1));

    if(Tuv.y > FLT_EPSILON && Tuv.z > FLT_EPSILON && (Tuv.y + Tuv.z - 1.0f) < FLT_EPSILON) //Values for u and v are correct
    {
        if((Tuv.x - 1.0f) > FLT_EPSILON)
        {
            //We have an intersection, we return it the intersection vertex
            return vertex(arg.getPointOnRay(Tuv.x), &t_color, &t_normal, vertex::DIFFUSE);
        }
        //no intersection TODO Choose better return value when we don't have an intersection
        return vertex();
    }
    //no intersection
    return vertex();
}

colordbl triangle::getColor()
{
    return t_color;
}