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
#include "CollisionFloor.hpp"
#include "CollisionWall.hpp"
#include "Scene.hpp"
#include "Rect.hpp"
#include "Textures/textureLoader.hpp"
#include <GL/freeglut.h>
using namespace std;
int screenWidth = 800, screenWidthDiv2 = 400, screenHeight = 800, screenHeightDiv2 = 400;
#define FLOOR_DEBUG if(0)
#define LIGHTS if(0)
#define CURSOR_BALL if(1)
Camera *camera;
CollisionFloor* floors;
Wall* walls;
Scene *scene;
//Rect *scratchRectangle;
const double pi = acos(-1);
double radToDeg(double a) { return(a * 180 / pi); }

bool keyboard[256];
void keyboardUpHandler(unsigned char key, int x, int y) { keyboard[key] = false; }
void keyboardHandler(unsigned char key, int x, int y) { keyboard[key] = true; }

Vector *mouse; int mouseWidthLimit = 5, mouseHeightLimit = 5;
void passiveMotionHandler(int x, int y) {
  mouse->x += (screenWidthDiv2 - x) / 10.0, mouse->y += (y - screenHeightDiv2) / 10.0; // diff / x (angular acceleration), where x smoothes the increase of angular speed
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
  scene->getMovements(keyboard);
  glutPostRedisplay();
}

void drawGrid() {
  LIGHTS glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    for (int i = -16; i <= 16; i ++) {
      glColor3ub(  0, 100, 155); glVertex3d(-16, 11, i); glVertex3d(16, 11, i); // x axis
      glColor3ub(100,   0,   0); glVertex3d(i, 11, -16); glVertex3d(i, 11, 16); // z axis
    }
  glEnd();
  LIGHTS glEnable(GL_LIGHTING);
  for (int i = -16; i <= 16; i ++)
    for (int j = -16; j <= 16; j ++) {
      glPushMatrix();
        glTranslated(i, 11, j);
        glColor3ub(255, 255, 255); glutSolidSphere(0.1, 10, 10);
      glPopMatrix();
    }

}

void drawCursorBall() {
  glPushMatrix();
    glColor3ub(255, 255, 255);
    glTranslated(camera->position->x + camera->eyeDirection->x*2, camera->position->y + 1 + camera->eyeDirection->y*2, camera->position->z + camera->eyeDirection->z*2);
    glutSolidSphere(0.005, 10, 10);
  glPopMatrix();
}

void lightsSetup() {
  GLfloat materialAmbientAndDiffuse[] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialAmbientAndDiffuse); // Defines objects reflection to ambient and diffuse light
  GLfloat materialSpecular[] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular); // Defines objects reflection to specular light
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128); // Defines objects level of reflection (0 to 128)
  GLfloat lightAmbient[] = {0, 0, 0, 1}; glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  GLfloat lightDiffuse[] = {0.8, 0.8, 0.8, 1}; glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  GLfloat lightSpecular[] = {1, 1, 1, 1}; glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  GLfloat lightSpotCutoff = 10 + mouse->z; glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightSpotCutoff);
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
  GLfloat lightPosition[] = {(GLfloat) camera->position->x, (GLfloat) camera->position->y, (GLfloat) camera->position->z, 1};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  GLfloat lightSpotDirection[] = {(GLfloat) camera->eyeDirection->x, (GLfloat) camera->eyeDirection->y, (GLfloat) camera->eyeDirection->z};
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightSpotDirection);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    gluLookAt(camera->position->x, camera->position->y + 1, camera->position->z,
              camera->position->x + camera->eyeDirection->x*100, camera->position->y + 1 + camera->eyeDirection->y*100, camera->position->z + camera->eyeDirection->z*100,
              0, 1, 0);
    LIGHTS lightsSetup();

    CURSOR_BALL drawCursorBall();

    drawGrid();
    FLOOR_DEBUG {
      floors->drawFloorPolygons();
      walls->drawWallPolygons();
    }
    glPushMatrix();
    glTranslated(0, 11, 0);
    glColor3ub(255, 255, 255); glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    scene->draw();
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int width, int height) {
  screenWidth = width, screenHeight = max(1, height);
  screenWidthDiv2 = screenWidth >> 1, screenHeightDiv2 = screenHeight >> 1;
  
  glViewport(0, 0, screenWidth, screenHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65, (double) screenWidth / screenHeight, 0.01, 300);

  glMatrixMode(GL_MODELVIEW);
}

void init() {
  glEnable(GL_DEPTH_TEST);

  LIGHTS {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
  }

  GLuint texture = loadTexture("Textures/wall.bmp", 1024, 1024);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(65, (double) screenWidth / screenHeight, 0.01, 300);

  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  floors = new CollisionFloor();
  walls = new Wall();
  floors->buildFloor();
  walls->buildWalls();
  camera = new Camera(new Vector(0, 1, 0), floors, walls);
  mouse = new Vector(0, 0, 0);
  scene = new Scene();

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