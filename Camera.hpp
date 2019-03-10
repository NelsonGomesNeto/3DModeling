#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "CollisionFloor.hpp"
#include "CollisionWall.hpp"

class Camera {
public:
  Camera(Vector *pVector, CollisionFloor *pFloor, Wall *pWall);
  Vector *position, *angle, *forwardDirection, *rightDirection, *eyeDirection;
  double maxSpeed;
  void getMovements(bool keyboard[256], Vector *mouse);
  void update();
  CollisionFloor *pFloor;
  Wall *pWall;
};

#endif