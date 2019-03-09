#include "Camera.hpp"
#include "Vector.hpp"
#include <stdio.h>

Camera::Camera(Vector *p) {
  position = p;
  angle = new Vector(0, 0, 0);
  forwardDirection = new Vector(0, 0, 0.1), rightDirection = new Vector(0.1, 0, 0);
  maxSpeed = 0.1;
}

Camera::Camera(Vector *p, Floor *pFloor) {
  // TODO: COLLISION :)
  position = p;
  angle = new Vector(0, 0, 0);
  forwardDirection = new Vector(0, 0, 0.1), rightDirection = new Vector(0.1, 0, 0);
  maxSpeed = 0.1;
  this->pFloor = pFloor;
}

void Camera::getMovements(bool keyboard[256], Vector *mouse) {
  // cancel camera step if intended next position is out of bounds. Out of bounds means there's no floor polygon below camera.
  Vector* intended = position->copy();

  if (keyboard['w']) *intended += *forwardDirection;
  if (keyboard['s']) *intended -= *forwardDirection;
  if (keyboard['a']) *intended += *rightDirection;
  if (keyboard['d']) *intended -= *rightDirection;

  Vector* newPos = pFloor->checkHitBoxes(intended);

  position = newPos;

  if (keyboard['q']) { angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['e']) { angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['r']) { angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  if (keyboard['f']) { angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  // angle += mouse / sensitivity, mouse /= desacceleration

  if (keyboard['p']) mouse->z += 0.1;
  if (keyboard['P']) mouse->z -= 0.1;
  printf("%lf\n", mouse->z);
}

void Camera::update() {
  forwardDirection->set(0, 0, maxSpeed), rightDirection->set(maxSpeed, 0, 0);
  forwardDirection->rotateX(angle->x), rightDirection->rotateX(angle->x);
  forwardDirection->rotateY(-angle->y), rightDirection->rotateY(-angle->y);
}
