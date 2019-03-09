#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "Camera.hpp"
#include "Vector.hpp"
#include "Floor.hpp"
#include <GL/freeglut.h>
using namespace std;
int screenWidth = 800, screenWidthDiv2 = 400, screenHeight = 800, screenHeightDiv2 = 400;
bool FLOOR_DEBUG = true;
Camera *camera;
Floor* floors;
const double pi = acos(-1);
double radToDeg(double a) { return(a * 180 / pi); }

bool keyboard[256];
void keyboardUpHandler(unsigned char key, int x, int y) { keyboard[key] = false; }
void keyboardHandler(unsigned char key, int x, int y) { keyboard[key] = true; }

Vector *mouse; int mouseWidthLimit = 5, mouseHeightLimit = 5;
void passiveMotionHandler(int x, int y) {
  mouse->x -= (screenWidthDiv2 - x) / 10.0, mouse->y -= (screenHeightDiv2 - y) / 10.0; // diff / x (angular acceleration), where x smoothes the increase of angular speed
  if (mouse->x < -mouseWidthLimit) mouse->x = -mouseWidthLimit; else if (mouse->x > mouseWidthLimit) mouse->x = mouseWidthLimit;
  if (mouse->y < -mouseHeightLimit) mouse->y = -mouseHeightLimit; else if (mouse->y > mouseHeightLimit) mouse->y = mouseHeightLimit;
  keyboard['q'] = mouse->x > 0, keyboard['e'] = mouse->x < -0, // enables rotation on y axis
  keyboard['r'] = mouse->y > 0, keyboard['f'] = mouse->y < -0; // enables rotation on x axis
  glutWarpPointer(screenWidthDiv2, screenHeightDiv2);
}

void update(int value) {
  glutTimerFunc(10, update, 1);
  camera->getMovements(keyboard, mouse);
  camera->update();
  glutPostRedisplay();
}

void drawGrid() {
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    for (int i = -20; i <= 20; i ++) {
      glColor3ub(  0, 100, 155); glVertex3d(-20, 0, i); glVertex3d(20, 0, i); // x axis
      glColor3ub(100,   0,   0); glVertex3d(i, 0, -20); glVertex3d(i, 0, 20); // z axis
    }
  glEnd();
  glEnable(GL_LIGHTING);
  for (int i = -20; i <= 20; i ++)
    for (int j = -20; j <= 20; j ++) {
      glPushMatrix();
        glTranslated(i, 0, j);
        glColor3ub(255, 255, 255); glutSolidSphere(0.1, 10, 10);
      glPopMatrix();
    }
}

void lightsSetup() {
  GLfloat specularReflection[] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularReflection); // Defines objects reflection to specular light
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1); // Defines objects level of reflection (0 to 128)
  GLfloat lightAmbient[] = {1, 0, 0, 1}; glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  GLfloat lightDiffuse[] = {1, 0, 0, 1}; glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  GLfloat lightSpecular[] = {0, 0, 1, 1}; glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  GLfloat lightSpotCutoff = 10 + mouse->z; glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightSpotCutoff);
  GLfloat lightPosition[] = {camera->position->x, camera->position->y, camera->position->z, 1}; glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  GLfloat lightSpotDirection[] = {camera->forwardDirection->x, camera->forwardDirection->y, camera->forwardDirection->z}; glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightSpotDirection);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    gluLookAt(camera->position->x, camera->position->y, camera->position->z,
              camera->position->x + camera->forwardDirection->x*100, camera->position->y + camera->forwardDirection->y*100, camera->position->z + camera->forwardDirection->z*100,
              0, 1, 0);
    lightsSetup();

    glColor3ub(255, 255, 255);
    glPushMatrix();
      glTranslated(camera->position->x + camera->forwardDirection->x*100, camera->position->y + camera->forwardDirection->y*100, camera->position->z + camera->forwardDirection->z*100);
      glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    drawGrid();
    if (FLOOR_DEBUG)
      floors->drawFloorPolygons();
    glColor3ub(255, 255, 255); glutSolidSphere(0.5, 10, 10);
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int width, int height) {
  screenWidth = width, screenHeight = max(1, height);
  screenWidthDiv2 = screenWidth >> 1, screenHeightDiv2 = screenHeight >> 1;
  
  glViewport(0, 0, screenWidth, screenHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65, (double) screenWidth / screenHeight, 0.1, 300);

  glMatrixMode(GL_MODELVIEW);
}

void init() {
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(65, (double) screenWidth / screenHeight, 0.1, 300);

  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  floors = new Floor();
  floors->buildFloor();
  camera = new Camera(new Vector(0, 1, 0), floors);
  mouse = new Vector(0, 0, 0);

  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("3DModeling");
    init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(10, update, 1);

  glutKeyboardFunc(keyboardHandler);
  glutKeyboardUpFunc(keyboardUpHandler);

  glutPassiveMotionFunc(passiveMotionHandler);
  glutSetCursor(GLUT_CURSOR_NONE);

  glutMainLoop();
}