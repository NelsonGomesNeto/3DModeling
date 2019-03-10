#ifndef Rect_HPP
#define Rect_HPP

#include "Vector.hpp"

class Rect {
private:
  Vector *position;
  double width, height, xAngle, yAngle;
public:
  Rect(Vector *position, double width, double height);
  Rect(Vector *position, double xAngle, double yAngle, double width, double height);
  void getMovements(bool keyboard[256]);
  void recalculate();
  void draw();
  void print();
};

#endif