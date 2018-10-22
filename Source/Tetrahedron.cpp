
#include "../Headers/Tetrahedron.h"

Tetrahedron::Tetrahedron() {

}

Tetrahedron::Tetrahedron(vertex tCenter) {
    tetra_center = tCenter;
    point1 = glm::vec4(tetra_center.coordinates.x + 0.5f, tetra_center.coordinates.y - 0.5f, tetra_center.coordinates.z - 0.5f, 1.0f );
    point2 = glm::vec4(tetra_center.coordinates.x - 0.5f, tetra_center.coordinates.y + 0.5f, tetra_center.coordinates.z - 0.5f, 1.0f );
    point3 = glm::vec4(tetra_center.coordinates.x - 0.5f, tetra_center.coordinates.y - 0.5f, tetra_center.coordinates.z - 0.5f, 1.0f );
    point4 = glm::vec4(tetra_center.coordinates.x, tetra_center.coordinates.y, tetra_center.coordinates.z + 0.5f, 1.0f );

    tetra_faces[0] = triangle(glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(0.0f, 1.0f, 0.0f),
                              direction(glm::cross((point2-point1), (point4 - point2))),
                              vertex::DIFFUSE);
    tetra_faces[1] = triangle(glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z),
                              glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(0.0f, 1.0f, 0.0f),
                              direction(glm::cross((point3-point2), (point4 - point3))),
                              vertex::DIFFUSE);
    tetra_faces[2] = triangle(glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point4.coordinates.x, point4.coordinates.y, point4.coordinates.z), colordbl(0.0f, 1.0f, 0.0f),
                              direction(glm::cross((point1-point3), (point4 - point1))),
                              vertex::DIFFUSE);
    tetra_faces[3] = triangle(glm::vec3(point3.coordinates.x, point3.coordinates.y, point3.coordinates.z),
                              glm::vec3(point1.coordinates.x, point1.coordinates.y, point1.coordinates.z),
                              glm::vec3(point2.coordinates.x, point2.coordinates.y, point2.coordinates.z), colordbl(0.0f, 1.0f, 0.0f),
                              direction(glm::cross((point1-point3), (point2 - point1))),
                              vertex::DIFFUSE);
}

vertex Tetrahedron::intersect(ray &arg) {

    return vertex();
}