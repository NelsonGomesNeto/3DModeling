#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vector.hpp"
#include <GL/freeglut.h>

class Light {
private:
  GLfloat position[4], direction[4], ambient[4], diffuse[4], specular[4], spotExponent, spotCutoff, constantAttenuation, linearAttenuation, quadraticAttenuation;
public:
  GLenum id;
  Light(GLenum id, GLfloat position[], GLfloat direction[], GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat spotExponent, GLfloat spotCutoff, GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation);
  void setup();
  void draw(GLUquadric *quadric);
};

#endif