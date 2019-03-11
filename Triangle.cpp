//
// Created by Lucas Amorim on 3/10/2019.
//

#include <GL/glut.h>
#include "Triangle.hpp"

Triangle::Triangle(Vector* vertices[3]) {
  this->vertices = vertices;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

Triangle::Triangle(Vector* vertices[3], int R, int G, int B, int A, int textureId) {
  this->vertices = vertices;
  this->R = R, this->G = G, this->B = B, this->A = A, this->textureId = textureId;
}

void Triangle::draw() {
  // glBindTexture(GL_TEXTURE_2D, this->textureId);
  glColor4ub(this->R, this->G, this->B, this->A);
  glBegin(GL_TRIANGLE_STRIP);
    // glTexCoord2d(0, 0);
    glVertex3d(this->vertices[0]->x, this->vertices[0]->y, this->vertices[0]->z);
    // glTexCoord2d(1, 0);
    glVertex3d(this->vertices[1]->x, this->vertices[1]->y, this->vertices[1]->z);
    // glTexCoord2d(1, 1);
    glVertex3d(this->vertices[2]->x, this->vertices[2]->y, this->vertices[2]->z);
  glEnd();
}
