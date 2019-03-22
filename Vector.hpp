#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
  double x, y, z;

  Vector(double x, double y, double z);
  void set(double x, double y, double z);
  double magSquared();
  Vector* limit(double max);
  Vector* mult(double n);
  Vector* div(double n);
  void print(bool nude);
  void rotateX(double angle);
  void rotateY(double angle);
  void operator+=(const Vector &a);
  void operator-=(const Vector &a);
  Vector* operator-(const Vector &a);
  Vector* operator-();
  Vector* operator+(const Vector &a);
  Vector *copy();
  Vector *cross(Vector *pVector);
  double dot(Vector *a);
  Vector *normalize();
};

#endif
