//
// Created by Lucas Amorim on 3/9/2019.
//

#ifndef INC_3DMODELING_WALL_HPP
#define INC_3DMODELING_WALL_HPP
#include <vector>
#include "CollisionPolygon.hpp"

class Wall {
private:
  vector<Polygon*> wallPolygons;
public:
  void addWallPolygon(Polygon* polygon);
  void drawWallPolygons();
  void buildWalls();
  bool checkHitBoxes(Vector *pVector, Vector *currentPos);
};


#endif //INC_3DMODELING_WALL_HPP
