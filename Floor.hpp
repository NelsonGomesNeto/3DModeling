#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include "Polygon.hpp"

class Floor {
private:
  vector<Polygon*> floorPolygons;
public:
  void addFloorPolygon(Polygon* polygon);
  void drawFloorPolygons();
  void buildFloor();

  bool checkHitBoxes(Vector *pVector);
};

#endif //FLOOR_H
