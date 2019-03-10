#ifndef Rect_HPP
#define Rect_HPP

#include "Vector.hpp"

class Rect {
public:
  double width, height, xAngle, yAngle;
  int colors[3];
  Vector *position;
  Rect(Vector *position, double width, double height);
  Rect(Vector *position, double xAngle, double yAngle, double width, double height);
  void getMovements(bool keyboard[256]);
  void recalculate();
  void draw();
  void print();
};

#endif