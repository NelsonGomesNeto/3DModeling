#include "Light.hpp"
#include <stdio.h>

Light::Light(GLenum id, GLfloat position[], GLfloat direction[], GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat spotExponent, GLfloat spotCutoff, GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation) {
  this->id = id;
  memcpy(this->position, position, sizeof(GLenum)*4);
  memcpy(this->direction, direction, sizeof(GLenum)*4);
  memcpy(this->ambient, ambient, sizeof(GLenum)*4);
  memcpy(this->diffuse, diffuse, sizeof(GLenum)*4);
  memcpy(this->specular, specular, sizeof(GLenum)*4);
  this->spotExponent = spotExponent;
  this->spotCutoff = spotCutoff;
  this->constantAttenuation = constantAttenuation;
  this->linearAttenuation = linearAttenuation;
  this->quadraticAttenuation = quadraticAttenuation;
}

void Light::setup() {
  glLightfv(this->id, GL_POSITION, this->position);
  glLightfv(this->id, GL_SPOT_DIRECTION, this->direction);
  glLightfv(this->id, GL_AMBIENT, this->ambient);
  glLightfv(this->id, GL_DIFFUSE, this->diffuse);
  glLightfv(this->id, GL_SPECULAR, this->specular);
  glLightf(this->id, GL_SPOT_EXPONENT, this->spotExponent);
  glLightf(this->id, GL_SPOT_CUTOFF, this->spotCutoff);
  glLightf(this->id, GL_CONSTANT_ATTENUATION, this->constantAttenuation);
  glLightf(this->id, GL_LINEAR_ATTENUATION, this->linearAttenuation);
  glLightf(this->id, GL_QUADRATIC_ATTENUATION, this->quadraticAttenuation);
}

