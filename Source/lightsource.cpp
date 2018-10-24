//
// Created by Ola Steen on 2018-10-22.
//

#include "../Headers/lightsource.h"


lightsource::lightsource()
{
    pointRaddiace = 100.0f;
    l_surface = triangle(glm::vec3(7.5f, 0.0f, 4.8f), glm::vec3(5.0f, 0.5f, 4.8f), glm::vec3(5.0f, -0.5f, 4.8f), colordbl(1.0f, 1.0f, 1.0f), direction(0.0, 0.0, -1.0), vertex::DIFFUSE);
}

float lightsource::calclight(vertex& vert, scene& sc, Sphere& s, Tetrahedron& tr)
{
    float totalIntensity = 0.0f;
    for(int i = 0; i< numOfSamples; ++i)
    {
        float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float v = 2.0f;
        while (u+v > 1.0f)
        {
            v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        glm::vec3 surfacePoint = (1.0f-u-v)*l_surface.t_vertices[0].coordinates + u*l_surface.t_vertices[1].coordinates + v*l_surface.t_vertices[2].coordinates;
        glm::vec3 direction = glm::normalize(surfacePoint - glm::vec3(vert.coordinates));
        glm::vec3 start = glm::vec3(vert.coordinates) + 0.1f*direction;
        vertex startPoint(glm::vec4(start, 1.0f));
        vertex endPoint(glm::vec4(surfacePoint, 1.0f), &l_surface.t_color, &l_surface.t_normal, vertex::DIFFUSE);
        ray toLight(startPoint, endPoint);
        ray toObject(endPoint, startPoint);

        vertex intersectionVert = findClosestIntersection(toLight, sc, s, tr);

        if(intersectionVert != vertex() && vert.distance(intersectionVert) < vert.distance(endPoint))
            continue;

        float cosThetaOut = fmaxf(toObject.getCosine(vert), 0.0f);
        float cosThetaIn = fmaxf(toLight.getCosine(endPoint), 0.0f);
        float distance = glm::length(glm::vec3(toLight.endPoint().coordinates)- glm::vec3(toLight.startPoint().coordinates));

        totalIntensity += (cosThetaOut*cosThetaIn)/pow(distance, 2.0f);
    }
    totalIntensity /= numOfSamples;

    return totalIntensity*pointRaddiace;
}

vertex lightsource::findClosestIntersection(ray& r, scene& sc, Sphere& s, Tetrahedron& tr)
{
    float shortestDistance = std::numeric_limits<float>::max();//distance from camera to intersection
    vertex returnVert;
    vertex vert = sc.intersect(r);

    if(vert != vertex())
    {
        //we have an intersection
        shortestDistance = r.startPoint().distance(vert);
        returnVert=vert;
    }

    vert = tr.intersect(r);
    if(vert  != vertex() && r.startPoint().distance(vert) < shortestDistance)
    {
        //we have an intersection
        shortestDistance = r.startPoint().distance(vert);
        returnVert=vert;
    }
    vert = s.intersect(r);
    if(vert  != vertex() && r.startPoint().distance(vert) < shortestDistance)
    {
        shortestDistance = r.startPoint().distance(vert);
        returnVert=vert;
    }

    return returnVert;
}
