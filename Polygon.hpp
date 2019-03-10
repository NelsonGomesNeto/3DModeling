#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "Vector.hpp"
#include <vector>
using namespace std;

class Polygon {
private:
  vector<Vector*> vertices ,upperHitBox, lowerHitBox;
  Vector* normalVector;
  double maxUpperX = -100000, maxUpperY = -100000, maxUpperZ = -100000;
  double minUpperX = 100000, minUpperY = 100000, minUpperZ = 100000;
  double maxLowerX = -100000, maxLowerY = -100000, maxLowerZ = -100000;
  double minLowerX = 100000, minLowerY = 100000, minLowerZ = 100000;
  bool isFloor();
  double a, b, c, d;
public:
  Polygon(vector<Vector*> vertices);
  int nVertices();
  void draw();
  double heightAt(Vector *pVector);
  bool handleCollision(Vector *pVector);
};

#endif //POLYGON_HPP
