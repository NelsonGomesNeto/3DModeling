#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "Floor.hpp"
#include "Wall.hpp"

class Camera {
public:
  Camera(Vector *pVector, Floor *pFloor, Wall *pWall);
  Vector *position, *angle, *forwardDirection, *rightDirection, *eyeDirection;
  double maxSpeed;
  void getMovements(bool keyboard[256], Vector *mouse);
  void update();
  Floor *pFloor;
  Wall *pWall;
};

#endif