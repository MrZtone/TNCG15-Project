#include <iostream>
#include "Headers/camera.h"

int main() {
    camera cam = camera();
    scene scn;
    cam.render(scn);
    cam.createImage();
    return 0;
}