
#include "../Headers/Tetrahedron.h"

Tetrahedron::Tetrahedron() {

}

Tetrahedron::Tetrahedron(vertex tCenter) {
    tetra_center = tCenter;
    point1 = glm::vec4(tetra_center.coordinates.x + tetra_offset, tetra_center.coordinates.y - tetra_offset, tetra_center.coordinates.z - tetra_offset, 1.0f );
    point2 = glm::vec4(tetra_center.coordinates.x - tetra_offset, tetra_center.coordinates.y + tetra_offset, tetra_center.coordinates.z - tetra_offset, 1.0f );
    point3 = glm::vec4(tetra_center.coordinates.x - tetra_offset, tetra_center.coordinates.y - tetra_offset, tetra_center.coordinates.z - tetra_offset, 1.0f );
    point4 = glm::vec4(tetra_center.coordinates.x, tetra_center.coordinates.y, tetra_center.coordinates.z + tetra_offset, 1.0f );

    tetra_faces[0] = triangle(glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(0.0f, 1.0f, 0.0f),
                              direction(glm::vec4(glm::normalize(glm::vec3(glm::cross((point2-point1), (point4 - point1)))),1.0f)),
                              vertex::DIFFUSE);
    tetra_faces[1] = triangle(glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z),
                              glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(1.0f, 0.0f, 0.0f),
                              direction(glm::vec4(glm::normalize(glm::vec3((glm::cross((point3-point2), (point4 - point2))))),1.0f)),
                              vertex::DIFFUSE);
    tetra_faces[2] = triangle(glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(0.0f, 0.0f, 1.0f),
                              direction(glm::vec4(glm::normalize(glm::vec3(glm::cross((point1-point3), (point4 - point3)))),1.0f)),
                              vertex::DIFFUSE);
    tetra_faces[3] = triangle(glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z), colordbl(1.0f, 1.0f, 1.0f),
                              direction(glm::vec4(-glm::normalize(glm::vec3(glm::cross((point1-point3), (point2 - point3)))), 1.0f)),
                              vertex::DIFFUSE);
}

vertex Tetrahedron::intersect(ray &arg) {
    vertex closest;
    float shortestDistance = std::numeric_limits<float>::max();
    for(int i =0; i< 4; ++i)
    {
        vertex intersection = tetra_faces[i].rayIntersection(arg);
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