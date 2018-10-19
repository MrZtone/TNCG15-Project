
#include "../Headers/Tetrahedron.h"

Tetrahedron::Tetrahedron() {
    point1 = glm::vec4(0.0, 0.0, 0.0, 0.0);
    point2 = glm::vec4(0.0, 0.0, 0.0, 0.0);
    point3 = glm::vec4(0.0, 0.0, 0.0, 0.0);
    point4 = glm::vec4(0.0, 0.0, 0.0, 0.0);
}

Tetrahedron::Tetrahedron(glm::vec4 P1, glm::vec4 P2, glm::vec4 P3, glm::vec4 P4) {
    point1 = P1;
    point2 = P2;
    point3 = P3;
    point4 = P4;
}

vertex Tetrahedron::intersect(ray &arg) {
    return vertex();
}