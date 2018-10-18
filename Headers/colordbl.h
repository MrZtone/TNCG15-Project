
#ifndef PROJECT_COLORDBL_H
#define PROJECT_COLORDBL_H

#include "../glm/vec3.hpp"
#include <iostream>

class colordbl {
    friend class camera;

private:
    glm::vec3 color;

public:
    colordbl();
    colordbl(float R, float G, float B);
    colordbl(glm::vec3 c);
    const float& operator[](int i);
   friend  std::ostream& operator<<(std::ostream& os, const colordbl& obj);

};


#endif //PROJECT_COLORDBL_H
