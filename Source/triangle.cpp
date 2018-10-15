
#include "../Headers/triangle.h"
#include "../glm/glm.hpp"

triangle::triangle()
{
}

triangle::triangle(vertex v1, vertex v2, vertex v3, colordbl color, direction norm)
{
    t_vertices[0] = v1;
    t_vertices[1] = v2;
    t_vertices[2] = v3;
    t_color = color;
    t_normal = norm;
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

    glm::vec3 Tuv= glm::vec3(glm::dot(Q,E2), glm::dot(P,T), glm::dot(Q,D)) * (1/glm::dot(P,E2));

    if(Tuv.y > FLT_EPSILON && Tuv.z > FLT_EPSILON && (Tuv.y + Tuv.z - 1.0f) < FLT_EPSILON) //Values for u and v are correct
    {
        if((Tuv.x - 1.0f) > FLT_EPSILON)
        {
            //We have an intersection, we return it the intersection vertex
            return arg.getPointOnRay(Tuv.x);
        }
        //no intersection TODO Choose better return value when we don't have an intersection
        return vertex();
    }
    //no intersection
    return vertex();
}