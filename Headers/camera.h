
#ifndef PROJECT_CAMERA_H
#define PROJECT_CAMERA_H

#include "pixel.h"
#include "ray.h"
#include "scene.h"
#include "Sphere.h"
#include "../glm/mat4x4.hpp"


class camera {

public:
    static const int maxDepth = 2;

    camera();
    static const int width = 200;
    static const int height = 200;
    int intersectCounter;
    void render(scene& sc); //assigns value to viewplane
    void createImage(); //converts viewplane values to RGB values
    glm::mat4 toWorldCoordinates(vertex& v, ray& r, direction& N);
    glm::vec3 castRay(ray& r, vertex& v, scene& sc, triangle& T, float importance, int depth);

private:
    vertex eye1, eye2;
    pixel viewplane[width][height];
};


#endif //PROJECT_CAMERA_H
