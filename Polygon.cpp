#include <stdexcept>
#include "Polygon.hpp"
#include "Vector.hpp"
#include <GL/glut.h>

Polygon::Polygon(vector<Vector *> vertices) {
  if (vertices.size() < 2)
    throw std::invalid_argument("A polygon must have at least 3 vertices.");
  this->vertices = vertices;
  Vector *v1 = *this->vertices[1] - *this->vertices[0];
  Vector *v2 = *this->vertices[2] - *this->vertices[0];
  this->normalVector = v1->cross(v2)->normalize();
  this->normalVector->print();
  upperHitBox = vertices;
  lowerHitBox = vertices;
  Vector *k = this->normalVector->copy();
  // this will effectly represent the hitbox size
  if (this->isFloor())
    k->mult(0.1);
  else
    k->mult(2);
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
  // plane equation definition
  this->a = this->normalVector->x, this->b = this->normalVector->y, this->c = this->normalVector->z;
  this->d = -(this->a * this->vertices[0]->x + this->b * this->vertices[0]->y + this->c * this->vertices[0]->z);
}

int Polygon::nVertices() {
  return (int) this->vertices.size();
}

void Polygon::draw() {
  if (this->isFloor())
    glColor3ub(0, 127, 255);
  else
    glColor3ub(127, 255, 0);
  glBegin(GL_QUADS);
  for (Vector *v: this->vertices) {
    glNormal3d(-this->normalVector->x, -this->normalVector->y, -this->normalVector->z);
    glVertex3d(v->x, v->y, v->z);
  }
  glEnd();
  glPointSize(10);
  glColor3ub(255, 127, 0);
  glBegin(GL_POINTS);
  for (auto v: this->lowerHitBox) {
    glVertex3d(v->x, v->y, v->z);
  }
  glEnd();
  glColor3ub(255, 0, 0);
  glBegin(GL_POINTS);
  for (auto v: this->upperHitBox) {
    glVertex3d(v->x, v->y, v->z);
  }
  glEnd();
}

double Polygon::heightAt(Vector *pVector) {
  // ax + by + cz + d = 0
  // y = -(ax + cz + d) / b
  return (-(this->a * pVector->x + this->c * pVector->z + this->d) / this->b);
}

bool Polygon::isFloor() {
  return !(this->normalVector->y < 0.1 && this->normalVector->y > -0.1);
}

bool Polygon::handleCollision(Vector *pVector) {
  if (!this->isFloor()) {
    // handle Wall Collision
    if (this->minUpperX <= pVector->x && pVector->x <= this->maxUpperX
        && this->minUpperY <= pVector->y && pVector->y <= this->maxUpperY
        && this->minUpperZ <= pVector->z && pVector->z <= this->maxUpperZ)
      return true;
    return this->minLowerX <= pVector->x && pVector->x <= this->maxLowerX
           && this->minLowerY <= pVector->y && pVector->y <= this->maxLowerY
           && this->minLowerZ <= pVector->z && pVector->z <= this->maxLowerZ;

  }
  // floor check
  // check if point is inside upper hit box
  if (this->minUpperX <= pVector->x && pVector->x <= this->maxUpperX
      && this->minUpperY <= pVector->y && pVector->y <= this->maxUpperY
      && this->minUpperZ <= pVector->z && pVector->z <= this->maxUpperZ) {
    // inside upper hitbox, we need to snap pVector to the y coordinate of this floor
    pVector->y = this->heightAt(pVector);
    return true;
  }

  if (this->minLowerX <= pVector->x && pVector->x <= this->maxLowerX
      && this->minLowerY <= pVector->y && pVector->y <= this->maxLowerY
      && this->minLowerZ <= pVector->z && pVector->z <= this->maxLowerZ) {
    // inside lower hitbox, we need to snap pVector to the y coordinate of this floor
    pVector->y = this->heightAt(pVector);
    return true;
  }
  return false;

}


