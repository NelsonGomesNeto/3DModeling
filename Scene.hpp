#ifndef SCENE_HPP
#define SCENE_HPP

#include "Rect.hpp"
#include <vector>
using namespace std;

class Scene {
private:
  vector<Rect*> rectangles;
  bool isLoading;
public:
  Scene();
  void loadScene(bool keyboard[256]);
  void draw();
};

#endif