#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"

class Camera {
public:
  Vector *position, *angle, *forwardDirection, *rightDirection;
  double cosY, sinY, cosX, sinX;
  Camera(Vector *p);
  void getMovements(bool keyboard[256]);
  void update();
};
#endif