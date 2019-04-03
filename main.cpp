#if _WIN32
  #ifndef _WIN32
    #include <windows.h>
  #endif
#endif
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include "Vector.hpp"
#include "CollisionFloor.hpp"
#include "CollisionWall.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Rect.hpp"
#include "Textures/textureLoader.hpp"
#include "Door.hpp"
#include <GL/freeglut.h>
using namespace std;
int screenWidth = 800, screenWidthDiv2 = 400, screenHeight = 800, screenHeightDiv2 = 400;
#define FLOOR_DEBUG if(1)
#define LIGHTS if(1)
#define CURSOR_BALL if(1)
#define GRID if(0)
Camera *camera;
CollisionFloor* floors;
Wall* walls;
Scene *scene;
Doorr* door;
vector<Light*> lights;
GLUquadric *quadric = gluNewQuadric();
GLuint textureIds[10000];
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

bool loading = false;
void loadLights() {
  if (!loading && keyboard['3']) loading = true;
  else return;
  for (int i = 0; i < 8; i ++) glDisable(GL_LIGHT0 + i);
  lights.clear();
  char trash[1000];
  GLfloat position[4], direction[4], ambient[4], diffuse[4], specular[4], spotExponent, spotCutoff, constantAttenuation, linearAttenuation, quadraticAttenuation;
  FILE *filePtr = fopen("lights", "rb+");
  while (fscanf(filePtr, "%[^\n]", trash) != EOF &&
      fscanf(filePtr, "%f %f %f\n%f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f %f\n",
      &position[0], &position[1], &position[2],
      &direction[0], &direction[1], &direction[2],
      &ambient[0], &ambient[1], &ambient[2], &ambient[3],
      &diffuse[0], &diffuse[1], &diffuse[2], &diffuse[3],
      &specular[0], &specular[1], &specular[2], &specular[3],
      &spotExponent, &spotCutoff, &constantAttenuation, &linearAttenuation, &quadraticAttenuation) != EOF) {
    position[3] = 1;
    lights.push_back(new Light(GL_LIGHT0 + (GLenum) lights.size(), position, direction, ambient, diffuse, specular, spotExponent, spotCutoff, constantAttenuation, linearAttenuation, quadraticAttenuation));
    glEnable(lights[lights.size() - 1]->id);
  }
  loading = false;
}

void update(int value) {
  glutTimerFunc(10, update, 1);
  camera->getMovements(keyboard, mouse);
  camera->update();
  door->update();
  scene->getMovements(keyboard);
  loadLights();
  glutPostRedisplay();
}

void drawGrid() {
  double gridHeight = 0;
  LIGHTS glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    for (int i = -16; i <= 16; i ++) {
      glColor3ub(  0, 100, 155); glVertex3d(-16, gridHeight, i); glVertex3d(16, gridHeight, i); // x axis
      glColor3ub(100,   0,   0); glVertex3d(i, gridHeight, -16); glVertex3d(i, gridHeight, 16); // z axis
    }
  glEnd();
  LIGHTS glEnable(GL_LIGHTING);
  for (int i = -16; i <= 16; i ++)
    for (int j = -16; j <= 16; j ++) {
      glPushMatrix();
        glTranslated(i, gridHeight, j);
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
  for (Light *l: lights) l->setup();
  GLfloat position[4] = {(GLfloat) camera->position->x, (GLfloat) (camera->position->y + 1.5), (GLfloat) camera->position->z, 1},
  direction[4] = {(GLfloat) (camera->eyeDirection->x), (GLfloat) (camera->eyeDirection->y), (GLfloat) (camera->eyeDirection->z), 1};
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    gluLookAt(camera->position->x, camera->position->y + 1.5, camera->position->z,
              camera->position->x + camera->eyeDirection->x*100, camera->position->y + 1.5 + camera->eyeDirection->y*100, camera->position->z + camera->eyeDirection->z*100,
              0, 1, 0);
    LIGHTS lightsSetup();

    CURSOR_BALL drawCursorBall();

    GRID drawGrid();
    FLOOR_DEBUG {
      // floors->drawFloorPolygons();
      // walls->drawWallPolygons();
    }

    scene->draw(camera->position, textureIds);
    door->draw();
    for (Light *l: lights) l->draw(quadric);

    glDisable(GL_TEXTURE_2D);
    glColor4ub(176, 163, 119, 255);
    glPushMatrix();
      glTranslated(-5, 4, -3.7);
      glRotated(-90, 1, 0, 0);
      glutSolidCylinder(0.5, 10, 10, 50);
    glPopMatrix();
    glPushMatrix();
      glTranslated(-5, 4, -6.2);
      glRotated(-90, 1, 0, 0);
      glutSolidCylinder(0.5, 10, 10, 50);
    glPopMatrix();
    glPushMatrix();
      glTranslated(-5, 4, 3.7);
      glRotated(-90, 1, 0, 0);
      glutSolidCylinder(0.5, 10, 10, 50);
    glPopMatrix();
    glPushMatrix();
      glTranslated(-5, 4, 6.2);
      glRotated(-90, 1, 0, 0);
      glutSolidCylinder(0.5, 10, 10, 50);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
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
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glShadeModel(GL_SMOOTH);

    GLfloat materialAmbientAndDiffuse[] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialAmbientAndDiffuse); // Defines objects reflection to ambient and diffuse light
    GLfloat materialSpecular[] = {1, 1, 1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular); // Defines objects reflection to specular light
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128); // Defines objects level of reflection (0 to 128)
  }
  loadLights();

  textureIds[0] = loadTexture("Textures/wall.bmp", 1024, 1024);
  textureIds[1] = loadTexture("Textures/window.bmp", 343, 343);
  textureIds[2] = loadTexture("Textures/atari.bmp", 500, 359);
  textureIds[3] = loadTexture("Textures/keypad.bmp", 582, 674);
  textureIds[4] = loadTexture("Textures/radio.bmp", 482, 231);
  textureIds[5] = loadTexture("Textures/keyboard.bmp", 612, 292);
  textureIds[6] = loadTexture("Textures/floor.bmp", 225, 225);
  glEnable(GL_TEXTURE_2D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(65, (double) screenWidth / screenHeight, 0.01, 300);

  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  floors = new CollisionFloor();
  walls = new Wall();
  floors->buildFloor();
  walls->buildWalls();
  camera = new Camera(new Vector(-24, 0, 0), floors, walls);
  door = new Doorr(&(camera->position));
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
