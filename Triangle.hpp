//
// Created by Lucas Amorim on 3/10/2019.
//

#ifndef INC_3DMODELING_TRIANGLE_HPP
#define INC_3DMODELING_TRIANGLE_HPP


#include "Vector.hpp"

class Triangle {
public:
  Vector** vertices;
  Vector *normal;
  int R, G, B, A, textureId;
  Triangle(Vector* vertices[3]);
  Triangle(Vector* vertices[3], int R, int G, int B, int A, int textureId);
  void draw(GLuint* textureIds);
  double distanceTo(Vector *v);
private:
  void recursiveDraw(Vector *a, Vector *b, Vector *c, int depth);
};


#endif //INC_3DMODELING_TRIANGLE_HPP
