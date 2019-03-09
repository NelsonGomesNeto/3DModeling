//
// Created by Lucas Amorim on 3/8/2019.
//

#ifndef INC_3DMODELING_POLYGON_HPP
#define INC_3DMODELING_POLYGON_HPP

#include "Vector.hpp"
#include <vector>
using namespace std;

class Polygon {
private:
    vector<Vector*> vertices;
    Vector* normalVector;
    double maxUpperX = -100000, maxUpperY = -100000, maxUpperZ = -100000;
    double minUpperX = 100000, minUpperY = 100000, minUpperZ = 100000;
    double maxLowerX = -100000, maxLowerY = -100000, maxLowerZ = -100000;
    double minLowerX = 100000, minLowerY = 100000, minLowerZ = 100000;
    bool isFloor();

public:
    explicit Polygon(vector<Vector*> vertices);
    int nVertices();
    void draw();

    bool handleCollision(Vector *pVector);
};

#endif //INC_3DMODELING_POLYGON_HPP
