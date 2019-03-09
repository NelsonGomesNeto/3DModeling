//
// Created by Lucas Amorim on 3/8/2019.
//
#include <stdexcept>
#include "Polygon.hpp"
#include "Vector.hpp"
#include <GL/glut.h>

Polygon::Polygon(vector<Vector *> vertices) {
  if (vertices.size() < 2)
    throw std::invalid_argument("A polygon must have at least 3 vertices.");
  this->vertices = vertices;
  Vector* v1 = *this->vertices[1] - *this->vertices[0];
  Vector* v2 = *this->vertices[2] - *this->vertices[1];
  this->normalVector = v1->cross(v2)->unit();
  if (this->isFloor()) {
    vector<Vector*> upperHitBox = vertices, lowerHitBox = vertices;
    Vector* k = this->normalVector->copy();
    k->mult(-5);
    for (int i = 0; i < 4; i++) {
      upperHitBox.push_back(*upperHitBox[i] + *k);
      lowerHitBox.push_back(*lowerHitBox[i] - *k);
    }
    
    for (int i = 0; i < 8; i++) {
      if (upperHitBox[i]->x < this->minUpperX)
        this->minUpperX = upperHitBox[i]->x;
      if (upperHitBox[i]->x > this->maxUpperX)
        this->maxUpperX = upperHitBox[i]->x;

      if (upperHitBox[i]->y < this->minUpperY)
        this->minUpperY = upperHitBox[i]->y;
      if (upperHitBox[i]->y > this->maxUpperY)
        this->maxUpperY = upperHitBox[i]->y;
      
      if (upperHitBox[i]->z < this->minUpperZ)
        this->minUpperZ = upperHitBox[i]->z;
      if (upperHitBox[i]->z > this->maxUpperZ)
        this->maxUpperZ = upperHitBox[i]->z;

      if (lowerHitBox[i]->x < this->minLowerX)
        this->minLowerX = lowerHitBox[i]->x;
      if (lowerHitBox[i]->x > this->maxLowerX)
        this->maxLowerX = lowerHitBox[i]->x;

      if (lowerHitBox[i]->y < this->minLowerY)
        this->minLowerY = lowerHitBox[i]->y;
      if (lowerHitBox[i]->y > this->maxLowerY)
        this->maxLowerY = lowerHitBox[i]->y;

      if (lowerHitBox[i]->z < this->minLowerZ)
        this->minLowerZ = lowerHitBox[i]->z;
      if (lowerHitBox[i]->z > this->maxLowerZ)
        this->maxLowerZ = lowerHitBox[i]->z;
    }
  }
}

int Polygon::nVertices() {
  return (int)this->vertices.size();
}

void Polygon::draw() {
  glColor3ub(0, 127, 255);
  glBegin(GL_QUADS);
  for (auto v: this->vertices) {
    glVertex3d(v->x, v->y, v->z);
  }
  glEnd();
}

bool Polygon::isFloor() {
  return !(this->normalVector->y < 0.1 && this->normalVector->y > - 0.1);
}

bool Polygon::handleCollision(Vector *pVector) {
  if (!this->isFloor()) {
    // handle Wall Collision
    return false;
  }
  // floor check
  // check if point is inside upper hit box
  if (minUpperX <= pVector->x && pVector->x <= maxUpperX && minUpperY <= pVector->y && pVector->y <= maxUpperY && minUpperZ <= pVector->z && pVector->z <= maxUpperZ) {
    // inside upper hitbox, we need to snap pVector to the y coordinate of this floor
    printf("Inside upper Hitbox\n");
    return true;
  }

  if (minLowerX <= pVector->x && pVector->x <= maxLowerX && minLowerY <= pVector->y && pVector->y <= maxLowerY && minLowerZ <= pVector->z && pVector->z <= maxLowerZ) {
    // inside lower hitbox, we need to snap pVector to the y coordinate of this floor
    printf("Inside lower Hitbox\n");
    return true;
  }
  return false;

}


