#include "Camera.hpp"
#include "Vector.hpp"
#include <stdio.h>

Camera::Camera(Vector *p) {
  this->position = p;
  this->angle = new Vector(0, 0, 0);
  this->forwardDirection = new Vector(0, 0, 0.1), this->rightDirection = new Vector(0.1, 0, 0), this->eyeDirection = new Vector(0, 0, 0.1);
  this->maxSpeed = 0.1;
}

Camera::Camera(Vector *p, Floor *pFloor) {
  // TODO: COLLISION :)
  this->position = p;
  this->angle = new Vector(0, 0, 0);
  this->forwardDirection = new Vector(0, 0, 0.1), this->rightDirection = new Vector(0.1, 0, 0), this->eyeDirection = new Vector(0, 0, 0.1);
  this->maxSpeed = 0.1;
  this->pFloor = pFloor;
}

void Camera::getMovements(bool keyboard[256], Vector *mouse) {
  // cancel camera step if intended next position is out of bounds. Out of bounds means there's no floor polygon below camera.
  if (keyboard['w']) *this->position += *this->forwardDirection;
  if (keyboard['s']) *this->position -= *this->forwardDirection;
  if (keyboard['a']) *this->position += *this->rightDirection;
  if (keyboard['d']) *this->position -= *this->rightDirection;
  // intended->y -= 0.05;

  this->pFloor->checkHitBoxes(this->position); // fixes position in place

  if (keyboard['q']) { this->angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['e']) { this->angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['r']) { this->angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  if (keyboard['f']) { this->angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  // angle += mouse / sensitivity, mouse /= desacceleration

  // changes flashlight angle
  if (keyboard['p']) mouse->z += 0.1;
  if (keyboard['P']) mouse->z -= 0.1;
  // printf("%lf\n", mouse->z);
}

void Camera::update() {
  this->forwardDirection->set(0, 0, this->maxSpeed), this->rightDirection->set(this->maxSpeed, 0, 0), eyeDirection->set(0, 0, this->maxSpeed);
  this->forwardDirection->rotateX(this->angle->x), this->rightDirection->rotateX(this->angle->x); // this enables flight mode
  this->eyeDirection->rotateX(this->angle->x);
  this->forwardDirection->rotateY(this->angle->y), this->rightDirection->rotateY(this->angle->y), eyeDirection->rotateY(this->angle->y);
}
