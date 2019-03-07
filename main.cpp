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
#include <GL/freeglut.h>
using namespace std;
int screenWidth = 800, screenHeight = 800;
Camera *camera;
const double pi = acos(-1);
double radToDeg(double a) { return(a * 180 / pi); }

bool keyboard[256];
void keyboardUpHandler(unsigned char key, int x, int y) { keyboard[key] = false; }
void keyboardHandler(unsigned char key, int x, int y) { keyboard[key] = true; }

void update(int value) {
  glutTimerFunc(10, update, 1);
  camera->getMovements(keyboard);
  camera->update();
  glutPostRedisplay();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    // glRotated(radToDeg(camera->angle->x), 1, 0, 0);
    // glRotated(radToDeg(camera->angle->y), 0, 1, 0);
    gluLookAt(camera->position->x, camera->position->y, camera->position->z,
              camera->position->x + camera->forwardDirection->x*10, camera->position->y + camera->forwardDirection->y*10, camera->position->z + camera->forwardDirection->z*10,
              0, 1, 0);
    glColor3ub(0, 0, 255);
    glPushMatrix();
    glTranslated(camera->position->x + camera->forwardDirection->x*10, camera->position->y + camera->forwardDirection->y*10, camera->position->z + camera->forwardDirection->z*10);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
      for (int i = -10; i <= 10; i ++)
        for (int j = -10; j <= 10; j ++) {
          glVertex3d(-10, i, j); glVertex3d(10, i, j); // yz lines
          glVertex3d(i, -10, j); glVertex3d(i, 10, j); // xz lines
          glVertex3d(i, j, -10); glVertex3d(i, j, 10); // xy lines
        }
    glEnd();
  glPopMatrix();

  glutSwapBuffers();
}

void reshape(int width, int height) {
  height = max(1, height);
  screenWidth = width, screenHeight = height;
  
  glViewport(0, 0, screenWidth, screenHeight);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(60, (double) screenWidth / screenHeight, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  // gluLookAt(camera->position->x, camera->position->y, camera->position->z,
  //           camera->position->x, camera->position->y - 40, camera->position->z,
  //           0, 1, 0);
}

void init() {
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluPerspective(65, (double) screenWidth / screenHeight, 0.1, 300);

  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
  camera = new Camera(new Vector(0, 0, 0));
  printf("%3.3lf %3.3lf %3.3lf\n", camera->position->x, camera->position->y, camera->position->z);

  glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("3DModeling");
    init();
  glutDisplayFunc(display);
  // glutReshapeFunc(reshape);
  glutTimerFunc(10, update, 1);
  glutKeyboardFunc(keyboardHandler);
  glutKeyboardUpFunc(keyboardUpHandler);
  glutMainLoop();
}