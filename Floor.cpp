//
// Created by Lucas Amorim on 3/8/2019.
//

#include "Floor.hpp"
#include <stdexcept>

void Floor::addFloorPolygon(Polygon *polygon) {
  if (polygon->nVertices() != 4)
    throw std::invalid_argument("Must be a 4-vertex polygon to be added to the floor.");
  this->floorPolygons.push_back(polygon);
}

void Floor::drawFloorPolygons() {
  for (auto p: this->floorPolygons) {
    p->draw();
  }
}

void Floor::buildFloor() {
  vector<Vector*> v;
  v.push_back(new Vector(-10, 0, -10));
  v.push_back(new Vector(10, 0, -10));
  v.push_back(new Vector(10, 0, 10));
  v.push_back(new Vector(-10, 0, 10));
  Polygon* p = new Polygon(v);
  addFloorPolygon(p);
  v.clear();
  v.push_back(new Vector(10, 0, 10));
  v.push_back(new Vector(10, 5, 15));
  v.push_back(new Vector(5, 5, 15));
  v.push_back(new Vector(5, 0, 10));
  addFloorPolygon(new Polygon(v));
}

Vector *Floor::checkHitBoxes(Vector *pVector) {
  bool overPolygon = false;
  for (auto p: this->floorPolygons) {
    if (p->handleCollision(pVector))
      overPolygon = true;
  }
  if (!overPolygon)
    printf("out of bounds\n");
  return pVector;
}

