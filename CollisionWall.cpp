#include <math.h>
#include <stdexcept>
#include "CollisionWall.hpp"

void Wall::addWallPolygon(Polygon *polygon) {
  if (polygon->nVertices() != 4)
    throw std::invalid_argument("Must be a 4-vertex polygon to be added to the walls.");
  this->wallPolygons.push_back(polygon);
}

void Wall::drawWallPolygons() {
  for (Polygon *p: this->wallPolygons) {
    p->draw();
  }
}

void Wall::buildWalls() {
  vector<Vector*> v;
  v.push_back(new Vector(-20, -0.1, 20));
  v.push_back(new Vector(20, -0.1, 20));
  v.push_back(new Vector(20, 20, 20));
  v.push_back(new Vector(-20, 20, 20));
  Polygon *p = new Polygon(v);
  this->addWallPolygon(p);

  FILE *filePtr = fopen("scene", "rb+");
  int objects; fscanf(filePtr, "%d", &objects);
  char end, comment; while (fscanf(filePtr, "%c", &end) && end != '\n');
  while (objects --)
  {
    fscanf(filePtr, "%c", &comment);
    if (comment == '/') while (fscanf(filePtr, "%c", &end) && end != '\n');
    else fseek(filePtr, -1, SEEK_CUR);
    double x, y, z, xAngle, yAngle, width, height; int R, G, B, A, textureId;
    fscanf(filePtr, "%lf %lf %lf %lf %lf %lf %lf %d %d %d %d %d\n", &x, &y, &z, &xAngle, &yAngle, &width, &height, &R, &G, &B, &A, &textureId);
    Vector *w = new Vector(1, 0, 0), *h = new Vector(0, 1, 0), *p = new Vector(x, y, z);
    double pi = 3.141592653589793;
    if ((fabs(xAngle) > 10 && fabs(xAngle) < 170) || (fabs(xAngle) > 190 && fabs(xAngle) < 350)) continue;
    w->rotateX(xAngle * pi / 180.0), h->rotateX(xAngle * pi / 180.0);
    w->rotateY(yAngle * pi / 180.0), h->rotateY(yAngle * pi / 180.0);
    w->mult(width / 2.0), h->mult(height / 2.0);
    v.clear();
    v.push_back(*(*(-*w) + *h) + *p);
    v.push_back(*(*w + *h) + *p);
    v.push_back(*(*w - *h) + *p);
    v.push_back(*(*(-*w) - *h) + *p);
    this->addWallPolygon(new Polygon(v));
  }
  fclose(filePtr);
}

bool Wall::checkHitBoxes(Vector *pVector, Vector *original) {
  bool hitWall = false;
  for (Polygon *p: this->wallPolygons)
    if (p->handleCollision(pVector, original)) {
      hitWall = true;
    }

  return hitWall;
}
