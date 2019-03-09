#include "Vector.hpp"
#include <stdio.h>
#include <math.h>

Vector::Vector(double xx, double yy, double zz) {
  x = xx, y = yy, z = zz;
}

void Vector::set(double xx, double yy, double zz) {
  x = xx, y = yy, z = zz;
}

Vector* Vector::limit(int max) {
  double ms = magSquared();
  if (ms > pow(max, 2)) {
    div(sqrt(ms));
    mult(max);
  }
  return this;
}

Vector* Vector::div(double n) {
  x /= n;
  y /= n;
  z /= n;
  return this;
}

Vector* Vector::mult(double n) {
  x *= n;
  y *= n;
  z *= n;
  return this;
}

double Vector::magSquared() {
  return x * x + y * y + z * z;
}

void Vector::print() {
  printf("(%8.3lf,%8.3lf,%8.3lf), mag = %8.3lf\n", x, y, z, sqrt(x*x + y*y + z*z));

}

void Vector::rotateX(double angle) {
  /*
    1  0  0   x
    0  c -s . y
    0  s  c   z
  */
  double c = cos(angle), s = sin(angle), yy = y, zz = z;
  y =  c*yy + -s*zz;
  z =  s*yy +  c*zz;
}
void Vector::rotateY(double angle) {
  /*
    c  0  s   x
    0  1  0 . y
   -s  0  c   z
  */
  double c = cos(angle), s = sin(angle), xx = x, zz = z;
  x =  c*xx +  s*zz;
  z = -s*xx +  c*zz;
}

void Vector::operator+=(const Vector &a) {
  x += a.x, y += a.y, z += a.z;
}

void Vector::operator-=(const Vector &a) {
  x -= a.x, y -= a.y, z -= a.z;
}

Vector* Vector::operator-(const Vector &a) {
  return new Vector(this->x - a.x, this->y - a.y, this->z - a.z);
}

Vector *Vector::operator+(const Vector &a) {
  return new Vector(this->x + a.x, this->y + a.y, this->z + a.z);
}

Vector *Vector::copy() {
  return new Vector(this->x, this->y, this->z);
}

Vector *Vector::cross(Vector *pVector) {
  return new Vector(this->y * pVector->z - pVector->y * this->z, pVector->x * this->z - this->x * pVector->z, this->x * pVector->y - pVector->x * this->y);
}

Vector *Vector::unit() {
  div(sqrt(magSquared()));
  return this;
}
