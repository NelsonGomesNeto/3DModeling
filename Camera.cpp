#include "Camera.hpp"
#include "Vector.hpp"
#include <stdio.h>

Camera::Camera(Vector *p, CollisionFloor *pFloor, Wall *pWall) {
  this->position = p;
  this->angle = new Vector(0, 0, 0);
  this->forwardDirection = new Vector(0, 0, 0.1), this->rightDirection = new Vector(0.1, 0, 0), this->eyeDirection = new Vector(0, 0, 0.1), this->movementDirection = new Vector(0, 0, 0);
  this->maxSpeed = 0.1;
  this->pFloor = pFloor;
  this->pWall = pWall;
}

void Camera::getMovements(bool keyboard[256], Vector *mouse) {
  this->movementDirection->set(0, 0, 0);
  Vector* intended = position->copy();
  if (keyboard['w']) *this->movementDirection += *this->forwardDirection;
  if (keyboard['s']) *this->movementDirection -= *this->forwardDirection;
  if (keyboard['a']) *this->movementDirection += *this->rightDirection;
  if (keyboard['d']) *this->movementDirection -= *this->rightDirection;
  if (keyboard['W']) *this->movementDirection += *this->forwardDirection->div(40);
  if (keyboard['S']) *this->movementDirection -= *this->forwardDirection->div(40);
  if (keyboard['A']) *this->movementDirection += *this->rightDirection->div(40);
  if (keyboard['D']) *this->movementDirection -= *this->rightDirection->div(40);
  if (this->movementDirection->magSquared())
    this->movementDirection->normalize()->mult(this->maxSpeed);
  if (keyboard['W'] || keyboard['S'] || keyboard['A'] || keyboard['D'])
    this->movementDirection->div(40);
  *intended += *this->movementDirection;

 this->pFloor->checkHitBoxes(intended, this->position);
 this->pWall->checkHitBoxes(intended, this->position);
  this->position = intended;

  if (keyboard['q']) { this->angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['e']) { this->angle->y += mouse->x / 50.0, mouse->x /= 1.2; }
  if (keyboard['r']) { this->angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  if (keyboard['f']) { this->angle->x += mouse->y / 50.0, mouse->y /= 1.2; }
  // angle += mouse / sensitivity, mouse /= desacceleration

  // changes flashlight angle
  if (keyboard['p']) mouse->z += 0.1;
  if (keyboard['P']) mouse->z -= 0.1;
  // printf("%lf\n", mouse->z);

  // if (keyboard['2']) printf("(%8.3lf, %8.3lf, %8.3lf)\n", this->position->x + this->eyeDirection->x*2, this->position->y + 1 + this->eyeDirection->y*2, this->position->z + this->eyeDirection->z*2);
  if (keyboard['2']) printf("(%8.3lf, %.15lf, %8.3lf)\n", this->position->x, this->position->y, this->position->z);
}

void Camera::update() {
  this->forwardDirection->set(0, 0, this->maxSpeed), this->rightDirection->set(this->maxSpeed, 0, 0), eyeDirection->set(0, 0, this->maxSpeed);
  // this->forwardDirection->rotateX(this->angle->x), this->rightDirection->rotateX(this->angle->x); // this enables flight mode
  this->eyeDirection->rotateX(this->angle->x);
  this->forwardDirection->rotateY(this->angle->y), this->rightDirection->rotateY(this->angle->y), eyeDirection->rotateY(this->angle->y);
}
