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
#include <thread>
#include <vector>

int camera::pixelCounter = 0;
bool camera::MultiThread = true;

void camera::setPointers(scene* scne, Sphere* sp, lightsource* ls, Tetrahedron* tr)
{
    scn = scne;
    sph = sp;
    lightso = ls;
    tetra= tr;
}
void multirender(camera* cam, int quadrantIndex[])
{
    std::cout << "starting render" << std::endl;
    for(int i = quadrantIndex[0]; i <= quadrantIndex[1]; ++i )
    {
        for(int j= quadrantIndex[2]; j <= quadrantIndex[3]; ++j)
        {
            //go through each ray in the pixel
            glm::vec3 pixelColor(0.0f);
            for(int rayIndex = 0; rayIndex < pixel::numOfRays; ++rayIndex )
            {
                vertex vert = cam->findClosestIntersection(cam->getPixel(i,j).getrays(rayIndex), *(cam->scn), *(cam->sph), *(cam->tetra));
                if(vert != vertex())
                {
                    glm::vec3 vertexColor= cam->castRay(cam->getPixel(i,j).getrays(rayIndex), vert, *(cam->scn), *(cam->sph), 1.0f, 0, *(cam->lightso), *(cam->tetra));
                    pixelColor+=vertexColor;
                }
            }
            pixelColor/=pixel::numOfRays;
            cam->getPixel(i,j).setcolor(pixelColor);
            camera::pixelCounter++;
            std::cout << 100.0f*((float) camera::pixelCounter)/(camera::width*camera::height) << "%" << std::endl;
        }
    }
    std::cout << "render finished" << std::endl;
}


camera::camera()
{
    eye1 = vertex(-2.0f, 0.0f, 0.0f, 1.0f);
    eye2 = vertex(-1.0f, 0.0f, 0.0f, 1.0f);
    double pixelsize= 2.0/width;
    for(int i= 0; i < width; ++i)
    {
        for(int j= 0; j < height; ++j)
        {
            ray rays[pixel::numOfRays];
            for(int l = 0; l < pixel::numOfRays; ++l)
            {
                float rayY = (-1.0 + 2.0*i/width) + (rand()) / (static_cast <float> (RAND_MAX/pixelsize));
                float rayZ = (-1.0 + 2.0*j/height) + (rand()) / (static_cast <float> (RAND_MAX/pixelsize));
                rays[l] = ray(eye2, vertex(0.0, rayY, rayZ, 1.0));
            }
            viewplane[i][j] = pixel(rays);
        }
    }
    intersectCounter=0;
}

void camera::render(scene& sc, Sphere& s, lightsource& light, Tetrahedron& tr)
{

    if(MultiThread)
    {
        int dims1[] = {0,(width/2)-1,0,(height/2)-1};
        int dims2[] = {width/2,width-1,0,(height/2)-1};
        int dims3[] = {0,(width/2)-1,height/2,height-1};
        int dims4[] = {width/2,width-1,height/2,height-1};

        std::thread t1 = std::thread{multirender, this, dims1};
        std::thread t2 = std::thread{multirender, this, dims2};
        std::thread t3 = std::thread{multirender, this, dims3};
        std::thread t4 = std::thread{multirender, this, dims4};

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        return;
    }

    std::cout << "starting render" << std::endl;
    for(int i = 0; i < height; ++i )
    {
        for(int j= 0; j < width; ++j)
        {
            //go through each ray in the pixel
            glm::vec3 pixelColor(0.0f);
            for(int rayIndex = 0; rayIndex < pixel::numOfRays; ++rayIndex )
            {
                vertex vert = findClosestIntersection(viewplane[i][j].getrays(rayIndex), sc, s, tr);
                if(vert != vertex())
                {
                    glm::vec3 vertexColor= castRay(viewplane[i][j].getrays(rayIndex), vert, sc, s, 1.0f, 0, light, tr);
                    pixelColor+=vertexColor;
                }
            }
            pixelColor/=pixel::numOfRays;
            viewplane[i][j].setcolor(pixelColor);
            float allPixels = (float) width*height;
            std::cout << 100.0f*(i*width + j + 1.0f)/allPixels << " %" << std::endl;
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
            float R = (viewplane[i][j].getColor()[0]*255.0f)/1.0f;
            int r = (int) R;
            r = r > 255 ? 255: r;
            r = r < 0 ? 0: r;
            float G = (viewplane[i][j].getColor()[1]*255.0f)/1.0f;
            int g = (int) G;
            g = g > 255 ? 255: g;
            g = g < 0 ? 0: g;
            float B = (viewplane[i][j].getColor()[2]*255.0f)/1.0f;
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

glm::vec3 camera::castRay(ray& r, vertex& v, scene& sc, Sphere& s, float importance, int depth, lightsource& light, Tetrahedron& tr)
{
    float local = light.calclight(v, sc, s, tr);
    const int numOfDiffuseRays = 1;

    if(depth >= maxDepth)
    {
        return (v.v_color->color)*local;
    }

    if(v.surface == vertex::SPECULAR)
    {
        glm::vec4 incomming = glm::vec4(glm::vec3(r.endPoint().coordinates - r.startPoint().coordinates), 1.0f);
        glm::vec3 outgoing = glm::normalize(glm::reflect(glm::vec3(incomming), v.v_normal->vectorCoordinates));
        vertex rayEndpoint(glm::vec4(glm::vec3(v.coordinates) + outgoing, 1.0f));
        vertex rayStartpoint(glm::vec4(glm::vec3(v.coordinates) + 0.0001f*outgoing, 1.0f));

        ray outgoingRay = ray(rayStartpoint, rayEndpoint);

        vertex vert = findClosestIntersection(outgoingRay, sc, s, tr);
        if(vert != vertex())
        {
            intersectCounter++;
            glm::vec3 ret = castRay(outgoingRay, vert, sc, s, importance, depth+1, light, tr);
            return ret + 0.1f*(v.v_color->color)*local;
        }
    }
    else if(v.surface==vertex::DIFFUSE)
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
            vertex rayStartpoint(glm::vec4(glm::vec3(v.coordinates) + 0.0001f*glm::vec3(outgoing - v.coordinates), 1.0f));
            vertex rayEndpoint(outgoing);
            ray outgoingRay = ray(rayStartpoint, rayEndpoint);
            //float outgoingImportance = importance * fabs(glm::dot(((glm::vec3(cart))/glm::length(glm::vec3(cart))), v.v_normal->vectorCoordinates)/M_PI);
            float outgoingImportance = importance/M_PI;

            vertex vert = findClosestIntersection(outgoingRay, sc, s, tr);
            if(vert != vertex())
            {
                intersectCounter++;
                importanceArray[i] = outgoingImportance;
                raddianceArray[i] = castRay(outgoingRay, vert, sc, s, outgoingImportance, depth+1, light, tr);
            }
        }

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

vertex camera::findClosestIntersection(ray& r, scene& sc, Sphere& s, Tetrahedron& tr)
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

pixel& camera::getPixel(int i, int j)
{
    return viewplane[i][j];
}