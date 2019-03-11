//
// Created by Lucas Amorim on 3/11/2019.
//

#ifndef INC_3DMODELING_DOOR_HPP
#define INC_3DMODELING_DOOR_HPP


#include "Vector.hpp"

class Doorr {
private:
  int state = 0;
  int angle = 0;
  Vector** pos;
  bool cameraIsInsideRange();
public:
  void draw();
  void update();
  explicit Doorr(Vector **pVector);
};


#endif //INC_3DMODELING_DOOR_HPP
