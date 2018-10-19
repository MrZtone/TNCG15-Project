#include <iostream>
#include "Headers/camera.h"

int main() {
    camera* cam = new  camera();
    scene scn;
    cam->render(scn);
    cam->createImage();
    delete cam;
    return 0;
}