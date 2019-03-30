#include "Rect.hpp"
#include <stdio.h>
#include <math.h>
#include<algorithm>
#include <GL/freeglut.h>
const double pi = acos(-1);
using namespace std;

Rect::Rect(Vector *positwion, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = this->yAngle = 0;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

Rect::Rect(Vector *position, double xAngle, double yAngle, double width, double height) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = xAngle, this->yAngle = yAngle;
  this->R = rand() % 256, this->G = rand() % 256, this->B = rand() % 256, this->A = 255;
}

Rect::Rect(Vector *position, double xAngle, double yAngle, double width, double height, int R, int G, int B, int A, int textureId) {
  this->position = position;
  this->width = width, this->height = height;
  this->xAngle = xAngle, this->yAngle = yAngle;
  this->R = R, this->G = G, this->B = B, this->A = A, this->textureId = textureId;
  if (R == 255 && G == 255 && B == 255 && this->textureId == 0) {
    int decrementR = rand() % 60;
    this->R-= decrementR, this->G -= decrementR;
  }
}

void Rect::getMovements(bool keyboard[256]) {

}

void Rect::draw(GLuint* textureIds) {
  if (this->textureId > -1) glBindTexture(GL_TEXTURE_2D, textureIds[this->textureId]);
  else glDisable(GL_TEXTURE_2D);
  glPushMatrix();
    glColor4ub(this->R, this->G, this->B, this->A);
    glTranslated(this->position->x, this->position->y, this->position->z);
    glRotated(this->yAngle, 0, 1, 0);
    glRotated(this->xAngle, 1, 0, 0);
    double mult = 5;
    double wPieces = ceil(this->width * mult), hPieces = ceil(this->height * mult);
    double w = this->width / wPieces, bw = -this->width / 2.0, h = this->height / hPieces, bh = -this->height / 2.0;
    double ph = 1 / hPieces, pw = 1 / wPieces;
    // if (this->height == 0.22) printf("%lf %lf || %lf %lf || %lf %lf\n", pw, hPieces, ph, wPieces, w, h);
    glBegin(GL_QUADS);
      for (double i = 0; i < hPieces; i ++)
        for (double j = 0; j < wPieces; j ++) {
          glNormal3d(0, 0, 1); glTexCoord2d((j+1)*pw+0.03, i*ph); glVertex3d(bw + (j+1)*w, bh + i*h, 0);
          glNormal3d(0, 0, 1); glTexCoord2d((j+1)*pw+0.03, (i+1)*ph); glVertex3d(bw + (j+1)*w, bh + (i+1)*h, 0);
          glNormal3d(0, 0, 1); glTexCoord2d(j*pw+0.03, (i+1)*ph); glVertex3d(bw + j*w, bh + (i+1)*h, 0);
          glNormal3d(0, 0, 1); glTexCoord2d(j*pw+0.03, i*ph); glVertex3d(bw + j*w, bh + i*h, 0);
        }
    glEnd();
    // glBegin(GL_QUADS);
    //   glNormal3d(0, 0, 1); glTexCoord2d(1.03, 0); glVertex3d(-bw, bh, 0);
    //   glNormal3d(0, 0, 1); glTexCoord2d(1.03, 1); glVertex3d(-bw, -bh, 0);
    //   glNormal3d(0, 0, 1); glTexCoord2d(0.03, 1); glVertex3d(bw, -bh, 0);
    //   glNormal3d(0, 0, 1); glTexCoord2d(0.03, 0); glVertex3d(bw, bh, 0);
    // glEnd();
  glPopMatrix();
  if (this->textureId == -1) glEnable(GL_TEXTURE_2D);
}

void Rect::print() {
  this->position->print(true); printf(" %lf %lf %lf %lf\n", this->xAngle, this->yAngle, this->width, this->height);
}

double Rect::distanceTo(Vector *v) {
  double x = this->position->x, y = this->position->y, z = this->position->z;
  // double x = 0, y = 0, z = 0;
  // Vector *all[4];
  // all[0] = new Vector(this->position->x*0 + this->width / 2.0, this->position->y*0 + this->height / 2.0, 0);
  // all[1] = new Vector(this->position->x*0 - this->width / 2.0, this->position->y*0 + this->height / 2.0, 0);
  // all[2] = new Vector(this->position->x*0 + this->width / 2.0, this->position->y*0 - this->height / 2.0, 0);
  // all[3] = new Vector(this->position->x*0 - this->width / 2.0, this->position->y*0 - this->height / 2.0, 0);
  // double dist = 0;
  // for (int i = 0; i < 4; i ++) {
  //   all[i]->rotateX(this->xAngle);
  //   all[i]->rotateY(this->yAngle);
  //   all[i]->x += this->position->x, all[i]->y += this->position->y, all[i]->z += this->position->z;
  //   // x += all[i]->x, y += all[i]->y, z += all[i]->z;
  //   // double xx = v->x - all[i]->x, yy = v->y - all[i]->y, zz = v->z - all[i]->z;
  //   // dist = max(dist, sqrt(xx*xx + yy*yy + zz*zz));
  // }
  // // return(dist);
  double xx = v->x - x, yy = v->y - y, zz = v->z - z;
  return(sqrt(xx*xx + yy*yy + zz*zz));
}
