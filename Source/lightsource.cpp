//
// Created by Ola Steen on 2018-10-22.
//

#include "../Headers/lightsource.h"


lightsource::lightsource()
{
    pointRaddiace = 100.0f;
    l_surface = triangle(glm::vec3(5.0f, 0.0f, 4.0f), glm::vec3(9.0f, 2.0f, 4.0f), glm::vec3(9.0f, -2.0f, 4.0f), colordbl(1.0f, 1.0f, 1.0f), direction(0.0, 0.0, -1.0), vertex::DIFFUSE);
}

float lightsource::calclight(vertex& vert, scene& sc, Sphere& s)
{
    float totalIntensity = 0.0f;
    for(int i = 0; i< numOfSamples; ++i)
    {
        float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float v = 2.0;
        while (u+v > 1.0f)
        {
            v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        }

        glm::vec3 surfacePoint = (1.0f-u-v)*l_surface.t_vertices[0].coordinates + u*l_surface.t_vertices[1].coordinates + v*l_surface.t_vertices[2].coordinates;
        vertex endPoint(glm::vec4(surfacePoint, 1.0f), &l_surface.t_color, &l_surface.t_normal, vertex::DIFFUSE);
        ray toLight(vert, endPoint);
        ray toObject(endPoint, vert);

        vertex intersectionVert = findClosestIntersection(toLight, sc, s);

        if(vert.distance(intersectionVert) < vert.distance(endPoint))
            continue;

        float cosThetaOut = fabs(toObject.getCosine(vert));
        float cosThetaIn = fmaxf(toLight.getCosine(endPoint), 0.0f);
        if( cosThetaIn < 0.0f || cosThetaOut < 0.0f)
        {
            std::cout << "we have negatives" << std::endl;
         }
        float distance = glm::length(glm::vec3(toLight.endPoint().coordinates)- glm::vec3(toLight.startPoint().coordinates));

        totalIntensity += (cosThetaOut*cosThetaIn)/distance;
    }
    totalIntensity /= numOfSamples;

    //std::cout << totalIntensity*pointRaddiace << std::endl;
    return totalIntensity*pointRaddiace;
}

vertex lightsource::findClosestIntersection(ray& r, scene& sc, Sphere& s)
{
    float shortestDistance = std::numeric_limits<float>::max();//distance from camera to intersection
    vertex vert = sc.intersect(r);
    if(vert != vertex())
    {
        //we have an intersection
        shortestDistance = r.startPoint().distance(vert);
    }

    vertex vertSphere = s.intersect(r);
    float sphereDistance= r.startPoint().distance(vertSphere);
    if(vertSphere != vertex() && sphereDistance < shortestDistance && fabs(sphereDistance) >= 3.0f)
    {
        shortestDistance = r.startPoint().distance(vertSphere);
        return vertSphere;
    }
    return vert;
}
