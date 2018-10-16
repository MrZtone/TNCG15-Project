#include <iostream>
#include "Headers/camera.h"

int main() {
    camera* cam = new camera();
    scene scn;
    cam->render(scn);
    cam->createImage();
    std::cout << "hey there" << std::endl;
    delete cam;
    return 0;
}