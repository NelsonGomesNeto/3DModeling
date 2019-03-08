#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"

class Camera {
public:
  Vector *position, *angle, *forwardDirection, *rightDirection;
  double maxSpeed;
  Camera(Vector *p);
  void getMovements(bool keyboard[256], Vector *mouse);
  void update();
};
#endif