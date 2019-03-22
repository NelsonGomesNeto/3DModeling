#include "CollisionFloor.hpp"
#include <stdexcept>

void CollisionFloor::addFloorPolygon(Polygon *polygon) {
  if (polygon->nVertices() != 4)
    throw std::invalid_argument("Must be a 4-vertex polygon to be added to the floor.");
  this->floorPolygons.push_back(polygon);
}

void CollisionFloor::drawFloorPolygons() {
  for (Polygon *p: this->floorPolygons) {
    p->draw();
  }
}

void CollisionFloor::buildFloor() {
  vector<Vector*> v;
//  v.push_back(new Vector(-20, 0, 20));
//  v.push_back(new Vector(20, 0, 20));
//  v.push_back(new Vector(20, 0, -20));
//  v.push_back(new Vector(-20, 0, -20));
//  Polygon *p = new Polygon(v);
//  this->addFloorPolygon(p);
  v.push_back(new Vector(-28, 5, 15));
  v.push_back(new Vector(-28, 0, 10));
  v.push_back(new Vector(-38, 0, 10));
  v.push_back(new Vector(-38, 5, 15));
  this->addFloorPolygon(new Polygon(v));
  v.clear();

  v.push_back(new Vector(-15, 0, -3));
  v.push_back(new Vector(-15, 0, 3));
  v.push_back(new Vector(-6, 4, 3));
  v.push_back(new Vector(-6, 4, -3));
  this->addFloorPolygon(new Polygon(v));

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
    if (!((abs(xAngle) > 10 && abs(xAngle) < 170) || (abs(xAngle) > 190 && abs(xAngle) < 350))) continue;
    w->rotateX(xAngle * pi / 180.0), h->rotateX(xAngle * pi / 180.0);
    w->rotateY(yAngle * pi / 180.0), h->rotateY(yAngle * pi / 180.0);
    w->mult(width / 2.0), h->mult(height / 2.0);
    v.clear();
    v.push_back(*(*(-*w) + *h) + *p);
    v.push_back(*(*w + *h) + *p);
    v.push_back(*(*w - *h) + *p);
    v.push_back(*(*(-*w) - *h) + *p);
    this->addFloorPolygon(new Polygon(v));
  }
  fclose(filePtr);
}

bool CollisionFloor::checkHitBoxes(Vector *pVector, Vector *original) {
  bool overPolygon = false;
  for (Polygon *p: this->floorPolygons)
    if (p->handleCollision(pVector, original)) {
      overPolygon = true;
    }
  return overPolygon;
}