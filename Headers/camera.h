
#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "vertex.h"
#include "pixel.h"
#include "triangle.h"
#include "ray.h"
#include "scene.h"


class camera {

public:
    camera();
    static const int width = 800;
    static const int height = 800;
    void render(scene& sc); //assigns value to viewplane
    void createImage(); //converts viewplane values to RGB values

private:
    vertex eye1, eye2;
    pixel viewplane[width][height];
};


#endif //PROJECT_CAMERA_H
