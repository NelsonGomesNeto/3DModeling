//
// Created by Lucas Amorim on 3/10/2019.
//

#include <GL/glut.h>
#include "Triangle.hpp"

Triangle::Triangle(Vector* vertices[3]) {
  this->vertices = vertices;
}

void Triangle::draw() {
  glColor3ub(255, 0, 0);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    glVertex3d(this->vertices[i]->x, this->vertices[i]->y, this->vertices[i]->z);
  }
  glEnd();
}
