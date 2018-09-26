
#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "vertex.h"
#include "pixel.h"
#include "triangle.h"
#include "ray.h"


class camera {

private:
    vertex eye1, eye2;
    pixel viewplane[800][800];

public:
    camera();
    void render(); //assigns value to viewplane
    void createImage(); //converts viewplane values to RGB values
};


#endif //PROJECT_CAMERA_H
