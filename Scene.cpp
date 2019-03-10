#include "Scene.hpp"
#include "Rect.hpp"
#include <stdio.h>
using namespace std;

Scene::Scene() {
  this->isLoading = false;
}

void Scene::loadScene(bool keyboard[256]) {
  if (!keyboard['L']) this->isLoading = false;
  else if (!this->isLoading && keyboard['L']) this->isLoading = true;
  if (!this->isLoading) return;
  rectangles.clear();
  FILE *f = fopen("scene", "r");
  int r; fscanf(f, "%d", &r);
  char end; while (fscanf(f, "%c", &end) && end != '\n'); // jumps a 
  while (r --)
  {
    double x, y, z, xAngle, yAngle, width, height;
    fscanf(f, "%lf %lf %lf %lf %lf %lf %lf", &x, &y, &z, &xAngle, &yAngle, &width, &height);
    rectangles.push_back(new Rect(new Vector(x, y, z), xAngle, yAngle, width, height));
  }
  fclose(f);
  this->isLoading = false;
}

void Scene::draw() {
  for (Rect *rectangle: this->rectangles) {
    rectangle->draw();
  }
}