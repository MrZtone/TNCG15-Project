//
// Created by Ola Steen on 2018-10-22.
//

#include "../Headers/lightsource.h"


lightsource::lightsource()
{
    pointRaddiace = 10.0f;
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

        //check for visibility
        glm::vec3 surfacePoint = (1.0f-u-v)*l_surface.t_vertices[0].coordinates + u*l_surface.t_vertices[1].coordinates * l_surface.t_vertices[2].coordinates;
        vertex endPoint(glm::vec4(surfacePoint, 1.0f), &l_surface.t_color, &l_surface.t_normal, vertex::DIFFUSE);
        ray toLight(vert, endPoint);
        ray toObject(endPoint, vert);
        float cosThetaOut = toObject.getCosine(vert);
        float cosThetaIN = toLight.getCosine(endPoint);
        float distance = glm::length(glm::vec3(toLight.endPoint().coordinates)- glm::vec3(toLight.startPoint().coordinates));

        totalIntensity += (cosThetaOut*cosThetaIN)/powf(distance, 2.0f);
    }
    totalIntensity /= numOfSamples;

    return totalIntensity;
    //repeat for a number of samples
}
