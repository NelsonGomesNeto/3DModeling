#include "Light.hpp"
#include <stdio.h>
#include <GL/freeglut.h>

Light::Light(GLenum id, GLfloat position[], GLfloat direction[], GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat spotExponent, GLfloat spotCutoff, GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation) {
  this->id = id;
  position[3] = direction[3] = 1;
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

void Light::draw(GLUquadric *quadric) {
  glDisable(GL_TEXTURE_2D);
  glPushMatrix();
    glTranslatef(this->position[0], this->position[1], this->position[2]);
    glRotated(90, 1, 0, 0);
    glColor3ub(255, 255, 255); glutSolidSphere(0.1, 10, 10);
    glColor4ub(255, 255, 255, 130); gluCylinder(quadric, 0, 3, 7, 10, 50);
  glPopMatrix();
  glEnable(GL_TEXTURE_2D);
}

