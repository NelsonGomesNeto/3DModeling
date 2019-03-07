#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"

class Camera {
public:
  Vector *position, *angle;
  double cosY, sinY, cosX, sinX;
  Camera(Vector *p);
};
#endif