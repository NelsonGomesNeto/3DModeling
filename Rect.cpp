#include "Rect.hpp"
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
const double pi = acos(-1);

Rect::Rect(Vector *positwion, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = this->yAngle = 0;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

Rect::Rect(Vector *position, double xAngle, double yAngle, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = xAngle, this->yAngle = yAngle;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

Rect::Rect(Vector *position, double xAngle, double yAngle, double width, double height, int R, int G, int B, int A, int textureId) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = xAngle, this->yAngle = yAngle;
  this->R = R, this->G = G, this->B = B, this->A = A, this->textureId = textureId;
}

void Rect::getMovements(bool keyboard[256]) {

}

void Rect::draw() {
  glPushMatrix();
    // glColor3ub(this->colors[0], this->colors[1], this->colors[2]);
    glColor4ub(this->R, this->G, this->B, this->A);
    glTranslated(this->position->x, this->position->y, this->position->z);
    glRotated(this->yAngle, 0, 1, 0);
    glRotated(this->xAngle, 1, 0, 0);
    glBegin(GL_QUAD_STRIP);
      glTexCoord2d(0, 1); glVertex3d(-this->width / 2.0, this->height / 2.0, 0);
      glTexCoord2d(1, 1); glVertex3d(this->width / 2.0, this->height / 2.0, 0);
      glTexCoord2d(0, 0); glVertex3d(-this->width / 2.0, -this->height / 2.0, 0);
      glTexCoord2d(1, 0); glVertex3d(this->width / 2.0, -this->height / 2.0, 0);
    glEnd();
    // glRectd(-this->width / 2.0, -this->height / 2.0, this->width / 2.0, this->height / 2.0);
  glPopMatrix();
}

void Rect::print() {
  this->position->print(true); printf(" %lf %lf %lf %lf\n", this->xAngle, this->yAngle, this->width, this->height);
}