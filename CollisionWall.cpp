//
// Created by Lucas Amorim on 3/9/2019.
//

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
  v.push_back(new Vector(-20, 0, 20));
  v.push_back(new Vector(20, 0, 20));
  v.push_back(new Vector(20, 20, 20));
  v.push_back(new Vector(-20, 20, 20));
  Polygon *p = new Polygon(v);
  addWallPolygon(p);
}

bool Wall::checkHitBoxes(Vector *pVector, Vector *currentPos) {
  bool hitWall = false;
  for (Polygon *p: this->wallPolygons)
    if (p->handleCollision(pVector)) {
      hitWall = true;
    }

  return hitWall;
}
