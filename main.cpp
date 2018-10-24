#include <iostream>
#include "Headers/camera.h"


int main() {
    camera* cam = new  camera();
    lightsource light;
    scene scn;
    Tetrahedron tr = Tetrahedron(glm::vec4(7.0f, -2.0f, -3.0f, 1.0f));
    Sphere s(vertex(glm::vec4(7.0f, 2.0f, -3.0f, 1.0f)), 1.5f, colordbl(1.0f, 1.0f, 1.0f));
    cam->setPointers(&scn, &s, &light, &tr);
    cam->render(scn, s, light, tr);
    cam->createImage();
    delete cam;
    return 0;
}

