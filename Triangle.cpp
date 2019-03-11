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
  // glColor3ub(this->colors[0], this->colors[1], this->colors[2]);
  glColor4ub(this->colors[0], this->colors[1], this->colors[2], 255);
  glBegin(GL_TRIANGLE_STRIP);
    // glTexCoord2d(0, 0);
    glVertex3d(this->vertices[0]->x, this->vertices[0]->y, this->vertices[0]->z);
    // glTexCoord2d(1, 0);
    glVertex3d(this->vertices[1]->x, this->vertices[1]->y, this->vertices[1]->z);
    // glTexCoord2d(1, 1);
    glVertex3d(this->vertices[2]->x, this->vertices[2]->y, this->vertices[2]->z);
  glEnd();
}
