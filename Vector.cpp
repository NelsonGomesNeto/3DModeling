#include "Vector.hpp"
#include <stdio.h>
#include <math.h>

Vector::Vector(double x, double y, double z) {
  this->x = x, this->y = y, this->z = z;
}

void Vector::set(double x, double y, double z) {
  this->x = x, this->y = y, this->z = z;
}

Vector* Vector::limit(double max) {
  double ms = magSquared();
  if (ms > max*max) this->mult(max / sqrt(ms));
  return this;
}

Vector* Vector::div(double n) {
  this->x /= n, this->y /= n, this->z /= n;
  return this;
}

Vector* Vector::mult(double n) {
  this->x *= n, this->y *= n, this->z *= n;
  return this;
}

double Vector::magSquared() {
  return this->x * this->x + this->y * this->y + this->z * this->z;
}

void Vector::print() {
  printf("(%8.3lf,%8.3lf,%8.3lf), mag = %8.3lf\n", this->x, this->y, this->z, sqrt(this->magSquared()));
}

void Vector::rotateX(double angle) {
  /*
    1  0  0   x
    0  c -s . y
    0  s  c   z
  */
  double c = cos(angle), s = sin(angle), yy = this->y, zz = this->z;
  this->y =  c*yy + -s*zz,
  this->z =  s*yy +  c*zz;
}
void Vector::rotateY(double angle) {
  /*
    c  0  s   x
    0  1  0 . y
   -s  0  c   z
  */
  double c = cos(angle), s = sin(angle), xx = this->x, zz = this->z;
  this->x =  c*xx +  s*zz,
  this->z = -s*xx +  c*zz;
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
  return new Vector(this->y * pVector->z - this->z * pVector->y, this->z * pVector->x - this->x * pVector->z, this->x * pVector->y - this->y * pVector->x);
}

Vector *Vector::normalize() {
  return this->div(sqrt(this->magSquared()));
}
