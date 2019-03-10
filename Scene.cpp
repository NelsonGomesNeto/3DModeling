#include "Scene.hpp"
#include "Rect.hpp"
#include <stdio.h>
using namespace std;

Scene::Scene() {
  this->isLoading = false;
}

void Scene::loadScene() {
  rectangles.clear();
  triangles.clear();
  FILE *f = fopen("scene", "r");
  int r; fscanf(f, "%d", &r);
  char end; while (fscanf(f, "%c", &end) && end != '\n'); // jumps a 
  while (r --)
  {
    double x, y, z, xAngle, yAngle, width, height;
    fscanf(f, "%lf %lf %lf %lf %lf %lf %lf", &x, &y, &z, &xAngle, &yAngle, &width, &height);
    rectangles.push_back(new Rect(new Vector(x, y, z), xAngle, yAngle, width, height));
  }
  fscanf(f, "%d", &r);
  while (fscanf(f, "%c", &end) && end != '\n'); // jumps a
  while (r --)
  {
    double v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z;
    fscanf(f, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &v1x, &v1y, &v1z, &v2x, &v2y, &v2z, &v3x, &v3y, &v3z);
    triangles.push_back(new Triangle( new Vector*[3]{new Vector(v1x, v1y, v1z), new Vector(v2x, v2y, v2z), new Vector(v3x, v3y, v3z)}));
  }
  fclose(f);
}

void Scene::draw() {
  for (Rect *rectangle: this->rectangles) {
    rectangle->draw();
  }
  for (Triangle* t: this->triangles) {
    t->draw();
  }
}

void Scene::getMovements(bool *keyboard) {
  if (keyboard['1']) {
    keyboard['1'] = false;
    loadScene();
  }

  Rect* rect = nullptr;
  if (!this->rectangles.empty())
    rect = this->rectangles.back();
  if (keyboard['n']) {
    printf("added new rect");
    keyboard['n'] = false;
    if (rect != nullptr)
      this->rectangles.push_back(new Rect(rect->position->copy(), rect->width, rect->height));
    else
      this->rectangles.push_back(new Rect(new Vector(0, 0, 0), 5, 5));
  }
  if (this->rectangles.empty())
    return;
  rect = this->rectangles.back();
  if (keyboard['u']) rect->position->x += 0.01;
  if (keyboard['j']) rect->position->x -= 0.01;
  if (keyboard['h']) rect->position->z += 0.01;
  if (keyboard['k']) rect->position->z -= 0.01;
  if (keyboard['o']) rect->position->y += 0.01;
  if (keyboard['l']) rect->position->y -= 0.01;


  if (keyboard['y']) {
    rect->yAngle -= 90;
    keyboard['y'] = false;
  }
  if (keyboard['i']) {
    rect->yAngle += 90;
    keyboard['i'] = false;
  }
  if (keyboard['t']) {
    rect->xAngle += 90;
    keyboard['t'] = false;
  }
  if (keyboard['g']) {
    rect->xAngle -= 90;
    keyboard['g'] = false;
  }

  if (keyboard['6']) rect->width -= 0.01;
  if (keyboard['7']) rect->width += 0.01;
  if (keyboard['8']) rect->height -= 0.01;
  if (keyboard['9']) rect->height += 0.01;

  if (keyboard['b']) rect->xAngle = rect->yAngle = 0;
  if (keyboard['v']) rect->print();
}
