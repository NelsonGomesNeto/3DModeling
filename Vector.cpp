#include "Vector.hpp"
#include <stdio.h>
#include <math.h>

Vector::Vector(double xx, double yy, double zz) {
  x = xx, y = yy, z = zz;
}

void Vector::set(double xx, double yy, double zz) {
  x = xx, y = yy, z = zz;
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