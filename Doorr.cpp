//
// Created by Lucas Amorim on 3/11/2019.
//

#include <GL/glut.h>
#include "Doorr.hpp"
#include "Vector.hpp"
#include "Camera.hpp"

Doorr::Doorr(void *camera) {
  this->camera = camera;
}

void Doorr::draw() {
  glPushMatrix();
  glTranslated(-4, 8, -1.6);
  glPushMatrix();
  glRotated(-angle, 0, 1, 0);
  glBegin(GL_QUADS);
  glVertex3d(0, 0, 0.05);
  glVertex3d(0, -8, 0.05);
  glVertex3d(0, -8, 1.6);
  glVertex3d(0, 0, 1.6);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBegin(GL_QUADS);
  glVertex3d(0, 0, 1.6);
  glVertex3d(0, -8, 1.6);
  glVertex3d(0, -8, 3.15);
  glVertex3d(0, 0, 3.15);
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
  auto *cam = (Camera*) this->camera;
  Vector* pos = cam->position;
  return pos->x < -3 && pos->x > -5 && pos->y > 3 && pos->y < 7 && pos->z < 1.6 && pos->z > -1.6;
}
