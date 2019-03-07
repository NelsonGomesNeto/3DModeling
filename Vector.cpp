#include "Vector.hpp"
#include <stdio.h>

Vector::Vector(double xx, double yy, double zz) {
  x = xx, y = yy, z = zz;
}

void Vector::print() {
  printf("(% 3.3lf, % 3.3lf, % 3.3lf)\n", x, y, z);
}