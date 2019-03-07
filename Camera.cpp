#include "Camera.hpp"
#include "Vector.hpp"

Camera::Camera(Vector *p) {
  position = p;
  angle = new Vector(0, 0, 0);
  sinY = sinX = 0, cosY = cosX = 1;
}