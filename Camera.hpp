#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
#include "Floor.hpp"

class Camera {
public:
    Camera(Vector *pVector, Floor *pFloor);

    Vector *position, *angle, *forwardDirection, *rightDirection;
  double maxSpeed;
  explicit Camera(Vector *p);
  void getMovements(bool keyboard[256], Vector *mouse);
  void update();

    Floor *pFloor;
};
#endif