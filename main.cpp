#include <iostream>
#include "Headers/camera.h"

int main() {
    camera* cam = new  camera();
    lightsource light;
    scene scn;
    Sphere s(vertex(glm::vec4(7.0f, -2.0f, 1.0f, 1.0f)), 1.5f, colordbl(1.0f, 1.0f, 1.0f));
    cam->setPointers(&scn, &s, &light);
    cam->render(scn, s, light);
    cam->createImage();
    delete cam;
    return 0;
}

