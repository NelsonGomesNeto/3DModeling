#ifndef Rect_HPP
#define Rect_HPP

#include "Vector.hpp"

class Rect {
public:
  double width, height, xAngle, yAngle;
  int R, G, B, A, textureId;
  Vector *position;
  Rect(Vector *position, double width, double height);
  Rect(Vector *position, double xAngle, double yAngle, double width, double height);
  Rect(Vector *position, double xAngle, double yAngle, double width, double height, int R, int G, int B, int A, int textureId);
  void getMovements(bool keyboard[256]);
  void recalculate();
  void draw();
  void print();
  double distanceTo(Vector *v);
};

#endif