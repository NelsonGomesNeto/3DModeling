#include "Scene.hpp"
#include "Rect.hpp"
#include <stdio.h>
#include <algorithm>
using namespace std;

Scene::Scene() {
  this->isLoading = false;
}

void Scene::loadScene() {
  rectangles.clear();
  triangles.clear();
  FILE *filePtr = fopen("scene", "rb+");
  int objects; fscanf(filePtr, "%d", &objects);
  char end, comment; while (fscanf(filePtr, "%c", &end) && end != '\n'); // jumps a 
  while (objects --)
  {
    fscanf(filePtr, "%c", &comment);
    if (comment == '/') while (fscanf(filePtr, "%c", &end) && end != '\n'); 
    else fseek(filePtr, -1, SEEK_CUR);
    double x, y, z, xAngle, yAngle, width, height; int R, G, B, A, textureId;
    fscanf(filePtr, "%lf %lf %lf %lf %lf %lf %lf %d %d %d %d %d\n", &x, &y, &z, &xAngle, &yAngle, &width, &height, &R, &G, &B, &A, &textureId);
    rectangles.push_back(new Rect(new Vector(x, y, z), xAngle, yAngle, width, height, R, G, B, A, textureId));
  }
  fscanf(filePtr, "%d", &objects);
  while (fscanf(filePtr, "%c", &end) && end != '\n');
  while (objects --)
  {
    fscanf(filePtr, "%c", &comment);
    if (comment == '/') while (fscanf(filePtr, "%c", &end) && end != '\n');
    else fseek(filePtr, -1, SEEK_CUR);
    double v1x, v1y, v1z, v2x, v2y, v2z, v3x, v3y, v3z; int R, G, B, A, textureId;
    fscanf(filePtr, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %d %d %d %d %d\n", &v1x, &v1y, &v1z, &v2x, &v2y, &v2z, &v3x, &v3y, &v3z, &R, &G, &B, &A, &textureId);
    triangles.push_back(new Triangle(new Vector*[3]{new Vector(v1x, v1y, v1z), new Vector(v2x, v2y, v2z), new Vector(v3x, v3y, v3z)}, R, G, B, A, textureId));
  }
  fclose(filePtr);
}

struct Pack {
  double dist; Rect* rectangle; Triangle* triangle;
  bool operator<(const Pack &a) const { return(dist > a.dist); }
};
void Scene::draw(Vector *observerPosition, GLuint* textureIds) {
  for (Rect *rectangle: this->rectangles) if (rectangle->A == 255) rectangle->draw(textureIds);
  for (Triangle *triangle: this->triangles) if (triangle->A == 255) triangle->draw();

  vector<Pack> toDraw;
  for (Rect *rectangle: this->rectangles) if (rectangle->A < 255) toDraw.push_back({rectangle->distanceTo(observerPosition), rectangle, nullptr});
  for (Triangle *triangle: this->triangles) if (triangle->A < 255) toDraw.push_back({triangle->distanceTo(observerPosition), nullptr, triangle});
  sort(toDraw.begin(), toDraw.end());

  for (Pack &p: toDraw) if (p.rectangle == nullptr) p.triangle->draw(); else p.rectangle->draw(textureIds);

  // for (Rect *rectangle: this->rectangles) {
  //   rectangle->draw();
  // }
  // for (Triangle* t: this->triangles) {
  //   t->draw();
  // }
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

