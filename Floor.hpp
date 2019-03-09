//
// Created by Lucas Amorim on 3/8/2019.
//

#ifndef INC_3DMODELING_FLOOR_H
#define INC_3DMODELING_FLOOR_H

#include <vector>
#include "Polygon.hpp"

class Floor {
private:
    vector<Polygon*> floorPolygons;
public:
    void addFloorPolygon(Polygon* polygon);
    void drawFloorPolygons();
    void buildFloor();

    Vector *checkHitBoxes(Vector *pVector);
};

#endif //INC_3DMODELING_FLOOR_H
