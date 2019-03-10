#include "Rect.hpp"
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
const double pi = acos(-1);

Rect::Rect(Vector *position, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = this->yAngle = 0;
}

Rect::Rect(Vector *position, double xAngle, double yAngle, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = xAngle, this->yAngle = yAngle;
}

void Rect::getMovements(bool keyboard[256]) {
  if (keyboard['u']) this->position->z += 0.1;
  if (keyboard['j']) this->position->z -= 0.1;
  if (keyboard['h']) this->position->x += 0.1;
  if (keyboard['k']) this->position->x -= 0.1;
  if (keyboard['o']) this->position->y += 0.1;
  if (keyboard['l']) this->position->y -= 0.1;

  if (keyboard['y']) this->yAngle -= 0.5;
  if (keyboard['i']) this->yAngle += 0.5;
  if (keyboard['t']) this->xAngle += 0.5;
  if (keyboard['g']) this->xAngle -= 0.5;

  if (keyboard['6']) this->width -= 0.1;
  if (keyboard['7']) this->width += 0.1;
  if (keyboard['8']) this->height -= 0.1;
  if (keyboard['9']) this->height += 0.1;
}

void Rect::draw() {
  glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslated(this->position->x, this->position->y, this->position->z);
    glRotated(this->yAngle, 0, 1, 0);
    glRotated(this->xAngle, 1, 0, 0);
    glRectd(-this->width / 2.0, -this->height / 2.0, this->width / 2.0, this->height / 2.0);
  glPopMatrix();
}

void Rect::print() {
  this->position->print(true); printf(" %lf %lf %lf %lf\n", this->xAngle, this->yAngle, this->width, this->height);
}