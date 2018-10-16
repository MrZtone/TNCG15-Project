
#ifndef PROJECT_COLORDBL_H
#define PROJECT_COLORDBL_H

#include "../glm/vec3.hpp"
#include <iostream>

class colordbl {

private:
    glm::vec3 color;

public:
    colordbl();
    colordbl(double R, double G, double B);
    const float& operator[](int i);
   friend  std::ostream& operator<<(std::ostream& os, const colordbl& obj);

};


#endif //PROJECT_COLORDBL_H
