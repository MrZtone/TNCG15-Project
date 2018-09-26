
#include "../Headers/scene.h"

scene::scene()
{
    colordbl WHITE= colordbl(1.0,1.0,1.0);
    direction FLOORNORMAL = direction(0.0, 0.0, 1.0);
    direction CEILINGNORMAL = direction(0.0, 0.0, -1.0);

    //TODO Add remaining triangles
    walls[0] = triangle(vertex(0.0, 0.0, -5.0, 0.0), vertex(0.0, 6.0, -5.0, 0.0), vertex(-3.0, 0.0, -5.0, 0.0), WHITE, FLOORNORMAL);
}
