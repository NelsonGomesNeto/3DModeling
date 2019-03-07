#include "Camera.hpp"
#include "Vector.hpp"
#include <stdio.h>

Camera::Camera(Vector *p) {
  position = p;
  angle = new Vector(0, 0, 0);
  forwardDirection = new Vector(0, 0, 1), rightDirection = new Vector(1, 0, 0);
  sinY = sinX = 0, cosY = cosX = 1;
}

void Camera::getMovements(bool keyboard[256]) {
  if (keyboard['w']) *position += *forwardDirection;
  if (keyboard['s']) *position -= *forwardDirection;
  if (keyboard['a']) *position += *rightDirection;
  if (keyboard['d']) *position -= *rightDirection;

  double day = 0, dax = 0;
  if (keyboard['q']) day -= 0.02;
  if (keyboard['e']) day += 0.02;
  if (keyboard['r']) dax -= 0.02;
  if (keyboard['f']) dax += 0.02;
  angle->x += dax, angle->y += day;
}

void Camera::update() {
  forwardDirection->set(0, 0, 1), rightDirection->set(1, 0, 0);
  forwardDirection->rotateX(angle->x), rightDirection->rotateX(angle->x);
  forwardDirection->rotateY(-angle->y), rightDirection->rotateY(-angle->y);
}