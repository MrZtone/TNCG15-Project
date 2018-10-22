#define _USE_MATH_DEFINES

#include "../Headers/camera.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../glm/glm.hpp"
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <limits>


camera::camera()
{
    eye1 = vertex(-2.0, 0.0, 0.0, 1.0);
    eye2 = vertex(-1.0, 0.0, 0.0, 1.0);
    double pixelsize= 2.0/width;
    for(int i= 0; i < width; ++i)
    {
        for(int j= 0; j < height; ++j)
        {
            //calculate endpoint for ray (on the viewplane)
            double rayY = (-1.0 + 2.0*i/width) + pixelsize/2.0;
            double rayZ = (-1.0 + 2.0*j/height) + pixelsize/2.0;
            viewplane[i][j] = pixel(ray(eye1, vertex(0.0, rayY, rayZ, 1.0)));
        }
    }
    intersectCounter=0;
}

void camera::render(scene& sc, Sphere& s, lightsource& light)
{
    std::cout << "starting render" << std::endl;
    for(int i = 0; i < height; ++i )
    {
        for(int j= 0; j < width; ++j)
        {
            //go through each ray in the pixel
            for(int rayIndex = 0; rayIndex < pixel::numOfRays; ++rayIndex )
            {
                vertex vert = findClosestIntersection(viewplane[i][j].getrays(rayIndex), sc, s, 0);
                colordbl vertexColor= castRay(viewplane[i][j].getrays(rayIndex), vert, sc, s, 1.0f, 0, light);
                viewplane[i][j].setcolor(vertexColor);
            }
            float allPixels = (float) width*height;
            std::cout << 100.0f*(i*width + j + 1.0f)/allPixels << " % complete" << std::endl;
        }
    }
    std::cout << "render finished" << std::endl;
}

void camera::createImage()
{
    std::cout << "starting to write to file" << std::endl;
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*width*height;  //w is your image width, h is image height, both int

    img = (unsigned char *)malloc(3*width*height);
    memset(img,0,3*width*height);

    for(int i = 0; i < width; ++i)
    {
        for(int j = 0; j < height; ++j)
        {
            int x=i;
            int y=(height-1)-j;
            float R = (viewplane[i][j].getColor()[0]*255.0f)/5.0f;
            int r = (int) R;
            r = r > 255 ? 255: r;
            r = r < 0 ? 0: r;
            float G = (viewplane[i][j].getColor()[1]*255.0f)/5.0f;
            int g = (int) G;
            g = g > 255 ? 255: g;
            g = g < 0 ? 0: g;
            float B = (viewplane[i][j].getColor()[2]*255.0f)/5.0f;
            int b = (int) B;
            b = b > 255 ? 255: b;
            b = b < 0 ? 0: b;
            img[(x+y*width)*3+2] = (unsigned char)(r);
            img[(x+y*width)*3+1] = (unsigned char)(g);
            img[(x+y*width)*3+0] = (unsigned char)(b);
        }
    }

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       width    );
    bmpinfoheader[ 5] = (unsigned char)(       width>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       width>>16);
    bmpinfoheader[ 7] = (unsigned char)(       width>>24);
    bmpinfoheader[ 8] = (unsigned char)(       height    );
    bmpinfoheader[ 9] = (unsigned char)(       height>> 8);
    bmpinfoheader[10] = (unsigned char)(       height>>16);
    bmpinfoheader[11] = (unsigned char)(       height>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<height; i++)
    {
        fwrite(img+(width*(height-i-1)*3),3,width,f);
        fwrite(bmppad,1,(4-(width*3)%4)%4,f);
    }

    free(img);
    fclose(f);
    std::cout << "image written to file" << std::endl;
    std::cout << "Intersectioncounter is " << intersectCounter << std::endl;
}

glm::mat4 camera::toWorldCoordinates(vertex& v, ray& r)
{
    glm::vec3 Z = glm::normalize(v.v_normal->vectorCoordinates);
    glm::vec3 I = glm::vec3(r.startPoint().coordinates) - glm::vec3(r.endPoint().coordinates);
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

//This is one dimensional, we need to return colors
glm::vec3 camera::castRay(ray& r, vertex& v, scene& sc, Sphere& s, float importance, int depth, lightsource& light)
{

    glm::vec3 cool = glm::normalize(glm::vec3(5.0f, 0.0f, 4.0f) - glm::vec3(v.coordinates));
    //float local = fabs(glm::dot(cool, glm::normalize(v.v_normal->vectorCoordinates)));
    //std::cout << "intensity is " << light.calclight(v, sc, s) << std::endl;
    float local = light.calclight(v, sc, s);
    const int numOfDiffuseRays = 3;
    if(depth >= maxDepth)
    {
        //5.0, 0.0, 4.0
        //RETURN LOCAL LIGHTING
        return (v.v_color->color)*local;
    }

    if(v.surface == vertex::SPECULAR)
    {
        glm::mat4 M = toWorldCoordinates(v, r);
        glm::vec4 incomming = glm::vec4(glm::vec3(r.endPoint().coordinates - r.startPoint().coordinates), 1.0f);
        incomming = glm::inverse(M)*incomming;
        float theta = acosf(incomming.z/sqrtf(powf(incomming.x, 2)+ powf(incomming.y, 2) + powf(incomming.z, 2)));
        vertex rayEndpoint(M*glm::vec4(-sinf(theta), 0.0f, cosf(theta), 1.0f));
        ray outgoingRay = ray(v, rayEndpoint);

        vertex vert = findClosestIntersection(outgoingRay, sc, s, depth);
        if(vert != vertex())
        {
            if(vert.surface == vertex::SPECULAR)
            {
                std::cout << "We have specular on specular reflection" << std::endl;
                std::cout << v.distance(vert) << std::endl;
            }
            intersectCounter++;
            //we have an intersection
            glm::vec3 ret = castRay(outgoingRay, vert, sc, s, importance, depth+1, light);
            return ret + 0.1f*(v.v_color->color)*local;
        }


    }
    /* if(specular)
     * calculate reflected ray
     * castRay(reflected ray, some_kind_of_importance, depth+1)
     * get radiance back from castRay
     */

    /* if(diffuse)
     * randomise numOfDiffuseRays many pairs of theta and phi
     * translate vector with spherical coordinates (theta, phi, 1) to cartesian
     * translate local cartesian coordinates to world coordinates. we call this vector R
     * castRay(R, some_kind_of_importance, depth+1)
     * get radiance back from castRay
     */
    if(v.surface==vertex::DIFFUSE)
    {
        glm::vec3 raddianceArray[numOfDiffuseRays] = {glm::vec3(0.0f, 0.0f, 0.0f)};
        float importanceArray[numOfDiffuseRays] = {0.0f};
        glm::mat4 M = toWorldCoordinates(v, r);

        for (int i = 0; i < numOfDiffuseRays; ++i)
        {
            float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(M_PI/2)));
            float phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(M_PI*2)));
            glm::vec4 cart(cosf(phi)*sinf(theta), sinf(phi)*sinf(theta), cosf(theta), 1.0f);
            glm::vec4 outgoing = M*cart;
            vertex rayEndpoint(outgoing);
            ray outgoingRay = ray(v, rayEndpoint);
            float outgoingImportance = importance * fabs(glm::dot(((glm::vec3(cart))/glm::length(glm::vec3(cart))), v.v_normal->vectorCoordinates)/M_PI);

            vertex vert = findClosestIntersection(outgoingRay, sc, s, depth);
            if(vert != vertex())
            {
                intersectCounter++;
                //we have an intersection
                importanceArray[i] = outgoingImportance;
                raddianceArray[i] = castRay(outgoingRay, vert, sc, s, outgoingImportance, depth+1, light);
            }
        }

        /* calculate radiance based on reflected rays's radiance and importance
         * calculate local light contribution
         * calculate total radiance
         * return radiance
         */

        glm::vec3 totalRadiance(0.0f, 0.0f, 0.0f);
        for(int i = 0; i < numOfDiffuseRays; ++i)
        {
            glm::vec3 temp = raddianceArray[i]*importanceArray[i];
            totalRadiance = totalRadiance + temp;
        }
        totalRadiance = (totalRadiance/importance)/((float)numOfDiffuseRays)+ (v.v_color->color)*local;
        totalRadiance.r = totalRadiance.r < 0.0f ? 0.0f : totalRadiance.r;
        totalRadiance.g =totalRadiance.g < 0.0f ? 0.0f : totalRadiance.g;
        totalRadiance.b = totalRadiance.b < 0.0f ? 0.0f : totalRadiance.b;
        return totalRadiance;
    }
}

vertex camera::findClosestIntersection(ray& r, scene& sc, Sphere& s, int depth)
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