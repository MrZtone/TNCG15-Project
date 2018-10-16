//
// Created by Ola Steen on 2018-09-12.
//

#include "../Headers/vertex.h"



//constructors
vertex::vertex()
{
    coordinates = glm::vec4(0.0, 0.0, 0.0, 0.0);
}

vertex::vertex(double X, double Y, double Z, double W)
{
    coordinates = glm::vec4(X, Y, Z, W);
}

vertex::vertex(glm::vec4 c)
{
    coordinates = c;
}

glm::vec3 vertex::operator -(vertex& arg1){
    glm::vec3 vector;
    vector = glm::vec3(arg1.coordinates - coordinates);
}
