
#ifndef PROJECT_COLORDBL_H
#define PROJECT_COLORDBL_H

#include "../glm/vec3.hpp"

class colordbl {

private:
    glm::vec3 color;

public:
    colordbl();
    colordbl(double R, double G, double B);

};


#endif //PROJECT_COLORDBL_H
