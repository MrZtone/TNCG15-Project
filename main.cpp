#include <iostream>
#include "Headers/camera.h"

int main() {
    camera* cam = new  camera();
    lightsource light;
    scene scn;
    Sphere s(vertex(glm::vec4(8.0f, 0.0f, 0.0f, 1.0f)), 1.0f, colordbl(1.0f, 1.0f, 1.0f));
    cam->render(scn, s, light);
    cam->createImage();
    delete cam;
    return 0;
}