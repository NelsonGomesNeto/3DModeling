#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "CollisionPolygon.hpp"

class CollisionFloor {
private:
  vector<Polygon*> floorPolygons;
public:
  void addFloorPolygon(Polygon* polygon);
  void drawFloorPolygons();
  void buildFloor();

  bool checkHitBoxes(Vector *pVector, Vector *original);
};

#endif //FLOOR_H
