#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
  double x, y, z;
  Vector(double xx, double yy, double zz);
  void set(double xx, double yy, double zz);
  void print();
  void rotateX(double angle);
  void rotateY(double angle);
  void operator+=(const Vector &a);
  void operator-=(const Vector &a);
};
#endif
