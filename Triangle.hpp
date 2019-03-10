//
// Created by Lucas Amorim on 3/10/2019.
//

#ifndef INC_3DMODELING_TRIANGLE_HPP
#define INC_3DMODELING_TRIANGLE_HPP


#include "Vector.hpp"

class Triangle {
public:
  Vector** vertices;
  Triangle(Vector* vertices[3]);

  void draw();
};


#endif //INC_3DMODELING_TRIANGLE_HPP
