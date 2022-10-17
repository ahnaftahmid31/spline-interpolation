#include <GL/glut.h>
#include <bits/stdc++.h>

#include "matrix.hpp"
#include "spline.hpp"
using namespace std;

#define Width 1920
#define Height 1080

double quad_table_x[30005];
double quad_table_y[30005];
double cubic_table_x[30005];
double cubic_table_y[30005];
int n;
double *x, *y;
int quad_table_size = 0;
int cubic_table_size = 0;

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

  double xScale = 8;
  double yScale = 8;

  // Quadratic (red color)
  glColor3ub(250, 20, 20);
  glPointSize(2);
  glPushMatrix();
  glBegin(GL_POINTS);
  for (int i = 0; i < quad_table_size; i++) {
    glVertex2d(xScale * quad_table_x[i], yScale * quad_table_y[i]);
  }
  glEnd();
  glPopMatrix();

  // Cubic (green color)
  glColor3ub(20, 250, 20);
  glPointSize(2);
  glPushMatrix();
  glBegin(GL_POINTS);
  for (int i = 0; i < cubic_table_size; i++) {
    glVertex2d(xScale * cubic_table_x[i], yScale * cubic_table_y[i]);
  }
  glEnd();
  glPopMatrix();

  // original x and y
  glColor3ub(20, 100, 220);
  glPointSize(6);
  glPushMatrix();
  glBegin(GL_POINTS);
  for (int i = 0; i < n; i++) {
    glVertex2d(xScale * x[i], yScale * y[i]);
  }
  glEnd();
  glPopMatrix();

  // last line
  glutSwapBuffers();
}

static void idle(void) { glutPostRedisplay(); }

const GLfloat high_shininess[] = {100.0f};

void take_input(int *n, double **x, double **y) {
  scanf("%d", n);
  *x = (double *)malloc(sizeof(double) * *n);
  *y = (double *)malloc(sizeof(double) * *n);
  for (int i = 0; i < *n; i++) {
    scanf("%lf %lf", *x + i, *y + i);
  }
}

void myInit(void) {
  take_input(&n, &x, &y);

  double **quad, **cubic;
  allocate_memory(&quad, 3 * n, 3 * n + 1);
  allocate_memory(&cubic, 4 * n, 4 * n + 1);

  quad_spline_matrix(quad, x, y, n);
  cubic_spline_matrix(cubic, x, y, n);

  puts("Quadratic spline matrix: ");
  // print_matrix(quad, 3 * (n - 1), 3 * (n - 1) + 1);
  print_quad_spline_matrix(quad, n);

  puts("Cubic spline matrix: ");
  // print_matrix(cubic, 4 * (n - 1), 4 * (n - 1) + 1);
  print_cubic_spline_matrix(cubic, n);

  double *sol = solve(quad, 3 * (n - 1));
  double *sol2 = solve(cubic, 4 * (n - 1));

  char ch[] = {'a', 'b', 'c', 'd'};

  cout << "\nQuad solutions:\n" << endl;
  for (int i = 0; i < 3 * (n - 1); i++) {
    printf("%c%d: %.8lf\n", ch[i % 3], (i / 3) + 1, sol[i]);
  }

  int k = 0, interval = 100;
  for (int i = 0; i < n - 1; i++) {
    double a = x[i], b = x[i + 1], c = (b - a) / interval;
    for (int j = 0; j < interval; j++) {
      double xi = a + c * j;
      quad_table_x[k] = xi;
      quad_table_y[k] =
          sol[i * 3] * xi * xi + sol[i * 3 + 1] * xi + sol[i * 3 + 2];
#ifdef DEBUG
      printf("f(%lf) = %lf\n", quad_table_x[k], quad_table_y[k]);
#endif
      k++;
    }
  }
  quad_table_size = k;

  cout << "\nCubic solutions:\n" << endl;
  for (int i = 0; i < 4 * (n - 1); i++) {
    printf("%c%d: %.8lf\n", ch[i % 4], (i / 4) + 1, sol2[i]);
  }

  k = 0;
  for (int i = 0; i < n - 1; i++) {
    double a = x[i], b = x[i + 1], c = (b - a) / interval;
    for (int j = 0; j < interval; j++) {
      double xi = a + c * j;
      cubic_table_x[k] = xi;
      cubic_table_y[k] = sol2[i * 4] * xi * xi * xi +
                         sol2[i * 4 + 1] * xi * xi + sol2[i * 4 + 2] * xi +
                         sol2[i * 4 + 3];
#ifdef DEBUG
      printf("f(%lf) = %lf\n", cubic_table_x[k], cubic_table_y[k]);
#endif
      k++;
    }
  }
  cubic_table_size = k;
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(Width, Height);
  glutInitWindowPosition(10, 50);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutCreateWindow("Quadratic spline");
  glutReshapeFunc(reshape);
  glClearColor(0, 0, 0, 1);
  glEnable(GL_COLOR_MATERIAL);

  myInit();

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();

  return EXIT_SUCCESS;
}