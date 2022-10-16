#include <bits/stdc++.h>
using namespace std;

#include <GL/glut.h>
#define Width 1920
#define Height 1080

static void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-Width / 2, Width / 2 - 1, -Height / 2, Height / 2 - 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void display(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3ub(255, 255, 255);
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex2i(-Width / 2, 0);
  glVertex2i(Width / 2, 0);
  glVertex2i(0, -Height / 2);
  glVertex2i(0, Height / 2);
  glEnd();
  glPopMatrix();

  // Draw here

  // glColor3ub(255, 0, 0);
  // glPointSize(10);
  // glPushMatrix();
  // glBegin(GL_POINTS);
  
  // glVertex2d(10, 10);

  // glEnd();
  // glPopMatrix();


  // last line
  glutSwapBuffers();
}

static void idle(void) { glutPostRedisplay(); }

void myInit(void) {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_COLOR_MATERIAL);

  // take input do stuff here


}
const GLfloat high_shininess[] = {100.0f};

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(10, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutCreateWindow("Quadratic spline");

  glutReshapeFunc(reshape);
  myInit();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();

  return EXIT_SUCCESS;
}