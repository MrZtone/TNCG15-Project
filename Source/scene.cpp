
#include "../Headers/scene.h"
#include <limits>

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
    walls[0] = triangle(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);
    walls[1] = triangle(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(0.0f, -6.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);
    walls[2] = triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);
    walls[3] = triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, 6.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);
    walls[4] = triangle(glm::vec3(10.0f, 0.0f, -5.0f), glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(10.0f, 6.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);
    walls[5] = triangle(glm::vec3(10.0f, 0.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(13.0f, 0.0f, -5.0f), WHITE, FLOORNORMAL, vertex::DIFFUSE);

    //DONE TRIANGLES OF CEILING
    walls[6] = triangle(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(-3.0f, 0.0f, 5.0f), glm::vec3(0.0f, 6.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);
    walls[7] = triangle(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(-3.0f, 0.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);
    walls[8] = triangle(glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(0.0f, 6.0f, 5.0f), glm::vec3(10.0f, 6.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);
    walls[9] = triangle(glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(10.0f, -6.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);
    walls[10] = triangle(glm::vec3(10.0f, 0.0f, 5.0f), glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(13.0f, 0.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);
    walls[11] = triangle(glm::vec3(10.0f, 0.0f, 5.0f), glm::vec3(13.0f, 0.0f, 5.0f), glm::vec3(10.0f, -6.0f, 5.0f), WHITE, CEILINGNORMAL, vertex::DIFFUSE);

    //DONE FLAT WALLS @ Y = -6 PLANE
    walls[12]= triangle(glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, 5.0f), glm::vec3(0.0f,-6.0f, 5.0f),colordbl(1.0f, 0.0f, 0.0f), direction(0.0f, 1.0f, 0.0f), vertex::DIFFUSE);
    walls[13]= triangle(glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(10.0f, -6.0f, 5.0f), colordbl(1.0f, 0.0f, 0.0f), direction(0.0f, 1.0f, 0.0f), vertex::DIFFUSE);

    //DONE FLAT WALLS @ Y = 6 plane
    walls[14]= triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(0.0f, 6.0f, 5.0f), glm::vec3(10.0, 6.0, 5.0),colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0), vertex::DIFFUSE);
    walls[15]= triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(0.0, 6.0, -5.0),colordbl(1.0, 0.0, 0.0), direction(0.0, 1.0, 0.0), vertex::DIFFUSE);

    //THEM SNEA-WALLSEN
    walls[16]= triangle(glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(0.0f, -6.0f, -5.0f), glm::vec3(0.0f, -6.0f, 5.0f),colordbl(1.0f, 1.0f, 0.0f), direction(0.8944, 0.4472, 0.0), vertex::DIFFUSE);
    walls[17]= triangle(glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(0.0f, -6.0f, 5.0f), glm::vec3(-3.0f, 0.0f, 5.0f),colordbl(1.0f, 1.0f, 0.0f), direction(0.8944, 0.4472, 0.0), vertex::DIFFUSE);

    walls[18]= triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(-3.0f, 0.0f, -5.0f), glm::vec3(-3.0f, 0.0f, 5.0f),colordbl(0.0f, 1.0f, 1.0f), direction(-0.8944f, 0.4472f, 0.0f), vertex::DIFFUSE);
    walls[19]= triangle(glm::vec3(0.0f, 6.0f, -5.0f), glm::vec3(-3.0f, 0.0f, 5.0f), glm::vec3(0.0f, 6.0f, 5.0f),colordbl(0.0f, 1.0f, 1.0f), direction(-0.8944f, 0.4472f, 0.0f), vertex::DIFFUSE);

    walls[20]= triangle(glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(10.0f, 6.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f),colordbl(1.0f, 0.0f, 1.0f), direction(-0.8944f, -0.4472f, 0.0f), vertex::DIFFUSE);
    walls[21]= triangle(glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(10.0f, 6.0f, 5.0f), glm::vec3(13.0f, 0.0f, 5.0f),colordbl(1.0f, 0.0f, 1.0f), direction(-0.8944f, -0.4472f, 0.0f), vertex::DIFFUSE);

    walls[22]= triangle(glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(13.0f, 0.0f, -5.0f), glm::vec3(13.0f, 0.0f, 5.0f),colordbl(0.4f, 0.1f, 0.8f), direction(0.8944f, -0.4472f, 0.0f), vertex::DIFFUSE);
    walls[23]= triangle(glm::vec3(10.0f, -6.0f, -5.0f), glm::vec3(13.0f, 0.0f, 5.0f), glm::vec3(10.0f, -6.0f, 5.0f),colordbl(0.4f, 0.1f, 0.8f), direction(0.8944f, -0.4472f, 0.0f), vertex::DIFFUSE);
}

vertex scene::intersect(ray& arg)
{
    vertex closest;
    float shortestDistance = std::numeric_limits<float>::max();
    for(int i =0; i< SIZE; ++i)
    {
        vertex intersection = walls[i].rayIntersection(arg);
        if(intersection != vertex())
        {
            float distance = arg.startPoint().distance(intersection);
            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                closest = intersection;
            }
        }
    }
    return closest;
}
