//
// Created by Lucas Amorim on 3/10/2019.
//

#include <GL/glut.h>
#include "Triangle.hpp"
#include "Vector.hpp"
#include <math.h>

Triangle::Triangle(Vector* vertices[3]) {
  this->vertices = vertices;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
  this->normal = (*this->vertices[1] - *this->vertices[0])->cross(*this->vertices[2] - *this->vertices[1])->normalize();
}

Triangle::Triangle(Vector* vertices[3], int R, int G, int B, int A, int textureId) {
  this->vertices = vertices;
  this->R = R, this->G = G, this->B = B, this->A = A, this->textureId = textureId;
  this->normal = (*this->vertices[1] - *this->vertices[0])->cross(*this->vertices[2] - *this->vertices[1])->normalize();
  //this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

void Triangle::recursiveDraw(Vector *a, Vector *b, Vector *c, int depth) {
  if (depth == -1) {
    glNormal3d(this->normal->x, this->normal->y, this->normal->z); glTexCoord2d(0, 0); glVertex3d(a->x, a->y, a->z);
    glNormal3d(this->normal->x, this->normal->y, this->normal->z); glTexCoord2d(1, 0); glVertex3d(b->x, b->y, b->z);
    glNormal3d(this->normal->x, this->normal->y, this->normal->z); glTexCoord2d(1, 1); glVertex3d(c->x, c->y, c->z);
    return;
  }
  Vector *mid = new Vector((a->x + b->x) / 2.0, (a->y + b->y) / 2.0, (a->z + b->z) / 2.0);
  this->recursiveDraw(c, a, mid, depth - 1), this->recursiveDraw(b, c, mid, depth - 1);
}

void Triangle::draw(GLuint* textureIds) {
  if (this->textureId > -1) glBindTexture(GL_TEXTURE_2D, textureIds[this->textureId]);
  else glDisable(GL_TEXTURE_2D);
  glColor4ub(this->R, this->G, this->B, this->A);
  Vector *a = *this->vertices[1] - *this->vertices[0], *b = *this->vertices[2] - *this->vertices[1];
  double triangleArea = sqrt((a->y*b->z - a->z*b->y)*(a->y*b->z - a->z*b->y) + (a->z*b->x - a->x*b->z)*(a->z*b->x - a->x*b->z) + (a->x*b->y - a->y*b->x)*(a->x*b->y - a->y*b->x)) / 2.0;
  int maxDepth = log2(triangleArea) + 4;
  maxDepth = -1 > maxDepth ? 2 : maxDepth;
  glBegin(GL_TRIANGLES);
    double ab = (*this->vertices[1] - *this->vertices[0])->dot(*this->vertices[1] - *this->vertices[0]), bc = (*this->vertices[2] - *this->vertices[1])->dot(*this->vertices[2] - *this->vertices[1]), ca = (*this->vertices[0] - *this->vertices[2])->dot(*this->vertices[0] - *this->vertices[2]);
    if (ab >= bc && ab >= ca)
      this->recursiveDraw(this->vertices[0], this->vertices[1], this->vertices[2], maxDepth);
    else if (bc >= ab && bc >= ca)
      this->recursiveDraw(this->vertices[1], this->vertices[2], this->vertices[0], maxDepth);
    else if (ca >= ab && ca >= bc)
      this->recursiveDraw(this->vertices[2], this->vertices[0], this->vertices[1], maxDepth);
  glEnd();
  if (this->textureId == -1) glEnable(GL_TEXTURE_2D);
}

double Triangle::distanceTo(Vector *v) {
  double x = 0, y = 0, z = 0;
  for (int i = 0; i < 3; i ++)
    x += this->vertices[i]->x, y += this->vertices[i]->y, z += this->vertices[i]->z;
  x /= 3, y /= 3, z /= 3;
  double xx = v->x - x, yy = v->y - y, zz = v->z - z;
  return(sqrt(xx*xx + yy*yy + zz*zz));
}
