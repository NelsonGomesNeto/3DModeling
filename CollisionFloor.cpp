//
// Created by Lucas Amorim on 3/8/2019.
//

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
  v.push_back(new Vector(-20, 0, 20));
  v.push_back(new Vector(20, 0, 20));
  v.push_back(new Vector(20, 0, -20));
  v.push_back(new Vector(-20, 0, -20));
  Polygon *p = new Polygon(v);
  this->addFloorPolygon(p);
  v.clear();
  v.push_back(new Vector(10, 0, 10));
  v.push_back(new Vector(10, 5, 15));
  v.push_back(new Vector(5, 5, 15));
  v.push_back(new Vector(5, 0, 10));
  this->addFloorPolygon(new Polygon(v));
}

bool CollisionFloor::checkHitBoxes(Vector *pVector) {
  bool overPolygon = false;
  for (Polygon *p: this->floorPolygons)
    if (p->handleCollision(pVector)) {
      overPolygon = true;
    }
  return overPolygon;
}

