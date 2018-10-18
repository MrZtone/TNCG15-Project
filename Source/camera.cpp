//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/camera.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../glm/matrix.hpp"
#include <cstdlib>
#include <math.h>


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
}

void camera::render(scene& sc)
{
    std::cout << "starting render" << std::endl;
    for(int i = 0; i < width; ++i )
    {
        for(int j= 0; j < height; ++j)
        {
            //go through each ray in the pixel
            for(int rayIndex = 0; rayIndex < pixel::numOfRays; ++rayIndex )
            {

                ray& r = viewplane[i][j].getrays(rayIndex);
                //send ray towards every scene
                for(int triangleIndex = 0; triangleIndex < scene::SIZE; ++triangleIndex)
                {
                    if(sc.getWallTriangle(triangleIndex).rayIntersection(r) != vertex())
                    {
                        //we have an intersection
                        colordbl vertexColor= sc.getWallTriangle(triangleIndex).getColor();
                        viewplane[i][j].setcolor(vertexColor);
                        //TODO Add support for multiple intersections! atm we cancel once we find one
                        break;
                    }
                }
            }
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
            float R = viewplane[i][j].getColor()[0]*255.0f;
            int r = (int) R;
            r = r > 255 ? 255: r;
            r = r < 0 ? 0: r;
            float G =viewplane[i][j].getColor()[1]*255.0f;
            int g = (int) G;
            g = g > 255 ? 255: g;
            g = g < 0 ? 0: g;
            float B =viewplane[i][j].getColor()[2]*255.0f;
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
}

glm::mat4 camera::toWorldCoordinates(vertex& v, ray& r, direction& N)
{
    glm::vec3 Z = N.vectorCoordinates;
    glm::vec3 I = glm::vec3(r.startPoint().coordinates) - glm::vec3(r.endPoint().coordinates);
    glm::vec3 X = glm::normalize(I - (I*Z)*Z);
    glm::vec3 Y = -(glm::cross(X,Z));

    glm::mat4 M1 = glm::mat4(1.0f);
    glm::mat4 M2 = glm::mat4(1.0f);
    M1[0][0] = X.x;
    M1[1][0] = X.y;
    M1[2][0] = X.z;
    M1[0][1] = Y.x;
    M1[1][1] = Y.y;
    M1[2][1] = Y.z;
    M1[0][2] = Z.x;
    M1[1][2] = Z.y;
    M1[2][2] = Z.z;

    M2[0][3] = - v.coordinates.x;
    M2[1][3] = - v.coordinates.y;
    M2[2][3] = - v.coordinates.z;

    return glm::inverse(M1*M2);
}

//This is one dimensional, we need to return colors
glm::vec3 camera::castRay(ray& r, vertex& v, scene& sc, triangle& T, float importance, int depth)
{
    const int numOfDiffuseRays = 16;
    if(depth >= maxDepth)
    {
        //RETURN LOCAL LIGHTING
        return (T.t_color.color);
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
    glm::vec3 raddianceArray[numOfDiffuseRays] = {glm::vec3()};
    float importanceArray[numOfDiffuseRays] = {0.0f};
    for (int i = 0; i < numOfDiffuseRays; ++i)
    {
        float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(M_PI/2)));
        float phi = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(M_PI*2)));
        glm::vec3 cart(cosf(phi)*sinf(theta), sinf(phi)*sinf(theta), cosf(theta));
        glm::mat4 M = toWorldCoordinates(v, r, T.t_normal);
        glm::vec3 outgoing = glm::vec3(M*glm::vec4(cart, 1.0));
        vertex rayEndpoint(glm::vec4(outgoing, 0.0f));
        ray outgoingRay = ray(v, rayEndpoint);

        for(int triangleIndex = 0; triangleIndex < scene::SIZE; ++triangleIndex)
        {
            //find
            vertex vert = sc.getWallTriangle(triangleIndex).rayIntersection(outgoingRay);
            if(vert != vertex())
            {
                //we have an intersection
                //float outgoingImportance = (cosf(glm::angle(T.t_normal.vectorCoordinates, outgoing))*cosf(glm::angle(sc.getWallTriangle(triangleIndex).t_normal.vectorCoordinates, -outgoing)))/powf(glm::length(outgoing), 2.0f));
                float outgoingImportance = glm::dot(outgoing, (T.t_normal.vectorCoordinates/glm::length(T.t_normal.vectorCoordinates)))/M_PI;
                importanceArray[i] = outgoingImportance;
                raddianceArray[i] = castRay(outgoingRay, vert, sc, sc.getWallTriangle(triangleIndex), outgoingImportance, ++depth);
                //TODO Add support for multiple intersections! atm we cancel once we find one
                break;
            }
        }
    }

    /* calculate radiance based on reflected rays's radiance and importance
     * calculate local light contribution
     * calculate total radiance
     * return radiance
     */

    glm::vec3 totalRadiance;
    for(int i = 0; i < numOfDiffuseRays; ++i)
    {
        totalRadiance += raddianceArray[i]*importanceArray[i];
    }

    return (totalRadiance/importance)/((float)numOfDiffuseRays);
}