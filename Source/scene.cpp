
#include "../Headers/scene.h"

triangle& scene::getWallTriangle(int index)
{
    return walls[index];
};

scene::scene()
{
    colordbl WHITE= colordbl(1.0,1.0,1.0);
    direction FLOORNORMAL = direction(0.0, 0.0, 1.0);
    direction CEILINGNORMAL = direction(0.0, 0.0, -1.0);

    //DONE TRIANGLES OF FLOOR
    walls[0] = triangle(vertex(0.0, 0.0, -5.0, 0.0), vertex(0.0, 6.0, -5.0, 0.0), vertex(-3.0, 0.0, -5.0, 0.0), WHITE, FLOORNORMAL);
    walls[1] = triangle(vertex(0.0, 0.0, -5.0, 0.0), vertex(-3.0, 0.0, -5.0, 0.0), vertex(0.0, -6.0, -5.0, 0.0), WHITE, FLOORNORMAL);
    walls[2] = triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(0.0, -6.0, -5.0, 0.0), vertex(10.0, -6.0, -5.0, 0.0), WHITE, FLOORNORMAL);
    walls[3] = triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(10.0, -6.0, -5.0, 0.0), vertex(10.0, 6.0, -5.0, 0.0), WHITE, FLOORNORMAL);
    walls[4] = triangle(vertex(10.0, 0.0, -5.0, 0.0), vertex(13.0, 0.0, -5.0, 0.0), vertex(10.0, 6.0, -5.0, 0.0), WHITE, FLOORNORMAL);
    walls[5] = triangle(vertex(10.0, 0.0, -5.0, 0.0), vertex(10.0, -6.0, -5.0, 0.0), vertex(13.0, 0.0, -5.0, 0.0), WHITE, FLOORNORMAL);

    //DONE TRIANGLES OF CEILING
    walls[6] = triangle(vertex(0.0, 0.0, 5.0, 0.0), vertex(-3.0, 0.0, 5.0, 0.0), vertex(0.0, 6.0, 5.0, 0.0), WHITE, CEILINGNORMAL);
    walls[7] = triangle(vertex(0.0, 0.0, 5.0, 0.0), vertex(0.0, -6.0, 5.0, 0.0), vertex(-3.0, 0.0, 5.0, 0.0), WHITE, CEILINGNORMAL);
    walls[8] = triangle(vertex(0.0, -6.0, 5.0, 0.0), vertex(0.0, 6.0, 5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0), WHITE, CEILINGNORMAL);
    walls[9] = triangle(vertex(0.0, -6.0, 5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0), vertex(10.0, -6.0, 5.0, 0.0), WHITE, CEILINGNORMAL);
    walls[10] = triangle(vertex(10.0, 0.0, 5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0), vertex(13.0, 0.0, 5.0, 0.0), WHITE, CEILINGNORMAL);
    walls[11] = triangle(vertex(10.0, 0.0, 5.0, 0.0), vertex(13.0, 0.0, 5.0, 0.0), vertex(10.0, -6.0, 5.0, 0.0), WHITE, CEILINGNORMAL);

    //DONE FLAT WALLS @ Y = -6 PLANE
    walls[12]= triangle(vertex(0.0, -6.0, -5.0, 0.0), vertex(10.0, -6.0, 5.0, 0.0), vertex(0.0,-6.0, 5.0, 0.0),colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0));
    walls[13]= triangle(vertex(0.0, -6.0, -5.0, 0.0), vertex(10.0, -6.0, -5.0, 0.0), vertex(10.0, -6.0, 5.0, 0.0), colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0));

    //DONE FLAT WALLS @ Y = 6 plane
    walls[14]= triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(0.0, 6.0, 5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0),colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0));
    walls[15]= triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0), vertex(0.0, 6.0, -5.0, 0.0),colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0));

    //THEM SNEA-WALLSEN
    walls[16]= triangle(vertex(-3.0, 0.0, -5.0, 0.0), vertex(0.0, -6.0, -5.0, 0.0), vertex(0.0, -6.0, 5.0, 0.0),colordbl(1.0, 1.0, 0.0), direction(0.8944, 0.4472, 0.0));
    walls[17]= triangle(vertex(-3.0, 0.0, -5.0, 0.0), vertex(0.0, -6.0, 5.0, 0.0), vertex(-3.0, 0.0, 5.0, 0.0),colordbl(1.0, 1.0, 0.0), direction(0.8944, 0.4472, 0.0));

    walls[18]= triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(-3.0, 0.0, -5.0, 0.0), vertex(-3.0, 0.0, 5.0, 0.0),colordbl(0.0, 1.0, 1.0), direction(-0.8944, 0.4472, 0.0));
    walls[19]= triangle(vertex(0.0, 6.0, -5.0, 0.0), vertex(-3.0, 0.0, 5.0, 0.0), vertex(0.0, 6.0, 5.0, 0.0),colordbl(0.0, 1.0, 1.0), direction(-0.8944, 0.4472, 0.0));

    walls[20]= triangle(vertex(13.0, 0.0, -5.0, 0.0), vertex(10.0, 6.0, -5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0),colordbl(1.0, 0.0, 1.0), direction(-0.8944, -0.4472, 0.0));
    walls[21]= triangle(vertex(13.0, 0.0, -5.0, 0.0), vertex(10.0, 6.0, 5.0, 0.0), vertex(13.0, 0.0, 5.0, 0.0),colordbl(1.0, 0.0, 1.0), direction(-0.8944, -0.4472, 0.0));

    walls[22]= triangle(vertex(10.0, -6.0, -5.0, 0.0), vertex(13.0, 0.0, -5.0, 0.0), vertex(13.0, 0.0, 5.0, 0.0),colordbl(0.4, 0.1, 0.8), direction(0.8944, -0.4472, 0.0));
    walls[23]= triangle(vertex(10.0, -6.0, -5.0, 0.0), vertex(13.0, 0.0, 5.0, 0.0), vertex(10.0, -6.0, 5.0, 0.0),colordbl(0.4, 0.1, 0.8), direction(0.8944, -0.4472, 0.0));
}
