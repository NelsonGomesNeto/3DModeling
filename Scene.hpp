#ifndef SCENE_HPP
#define SCENE_HPP

#include "Rect.hpp"
#include "Triangle.hpp"
#include <vector>
using namespace std;

class Scene {
private:
  vector<Rect*> rectangles;
  vector<Triangle*> triangles;
  bool isLoading;
public:
  Scene();
  void loadScene();
  void draw(Vector *observerPosition, GLuint* textureIds);

  void getMovements(bool pBoolean[256]);
};

#endif