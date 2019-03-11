//
// Created by Lucas Amorim on 3/11/2019.
//

#include <GL/glut.h>
#include <cstdio>
#include "Door.hpp"
#include "Vector.hpp"

Doorr::Doorr(Vector **pVector) {
  this->pos = pVector;
}

void Doorr::draw() {
  glPushMatrix();
  glColor4ub(0, 0, 0, 100);
  glTranslated(-4, 8, -1.6);
  glPushMatrix();
  glRotated(angle, 0, 1, 0);
  glBegin(GL_QUADS);
  glVertex3d(0, 0, 0.05);
  glVertex3d(0, -8, 0.05);
  glVertex3d(0, -8, 1.6);
  glVertex3d(0, 0, 1.6);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glTranslated(0, 0, 3.15);
  glRotated(-angle, 0, 1, 0);
  glBegin(GL_QUADS);
  glVertex3d(0, 0, -1.6);
  glVertex3d(0, -8, -1.6);
  glVertex3d(0, -8, 0);
  glVertex3d(0, 0, 0);
  glEnd();
  glPopMatrix();
  glPopMatrix();
}



void Doorr::update() {
  if (cameraIsInsideRange())
    state = 1;
  else
    state = 0;
  if (state == 0 && angle > 0)
    angle--;
  if (state == 1 && angle < 90)
    angle++;
}

bool Doorr::cameraIsInsideRange() {
  Vector* pos = *this->pos;
  return pos->x < 0 && pos->x > -8 && pos->y > 3 && pos->y < 7 && pos->z < 1.6 && pos->z > -1.6;
}


