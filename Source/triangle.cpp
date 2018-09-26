
#include "../Headers/triangle.h"

triangle::triangle()
{
}

triangle::triangle(vertex v1, vertex v2, vertex v3, colordbl color, direction norm)
{
    t_vertices[0] = v1;
    t_vertices[1] = v2;
    t_vertices[2] = v3;
    t_color = color;
    t_normal = norm;
}