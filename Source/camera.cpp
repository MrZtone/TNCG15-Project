//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/camera.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

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
                    std::cout << "one ray" << std::endl;
                    if(sc.getWallTriangle(triangleIndex).rayIntersection(r) != vertex())
                    {
                        //we have an intersection
                        viewplane[i][j].setcolor(sc.getWallTriangle(triangleIndex).getColor());
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

    int picture[width][height];
    for(int i = 0; i < width; ++i)
    {
        for(int j = 0; j < height; ++j)
        {
            int x=i;
            int y=(height-1)-j;
            int r = (int) viewplane[i][j].getColor()[0]*255;
            r = r > 255 ? 255: r;
            r = r < 0 ? 0: r;
            int g = (int) viewplane[i][j].getColor()[1]*255;
            r = g > 255 ? 255: g;
            r = g < 0 ? 0: g;
            int b = (int) viewplane[i][j].getColor()[2]*255;
            r = b > 255 ? 255: b;
            r = b < 0 ? 0: b;
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
