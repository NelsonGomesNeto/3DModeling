//
// Created by Lucas Amorim on 3/10/2019.
//

#include <GL/glut.h>
#include "Triangle.hpp"

Triangle::Triangle(Vector* vertices[3]) {
  this->vertices = vertices;
  this->colors[0] = rand() % 256;
  this->colors[1] = rand() % 256;
  this->colors[2] = rand() % 256;
}

void Triangle::draw() {
  glColor3ub(this->colors[0], this->colors[1], this->colors[2]);
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 3; i++) {
    glVertex3d(this->vertices[i]->x, this->vertices[i]->y, this->vertices[i]->z);
  }
  glEnd();
}
