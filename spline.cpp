#include "spline.hpp"

#include <bits/stdc++.h>
using namespace std;

// mat is the 3n * 3n matrix, *x is the input x array,
// *y is input y array, and n is the sizeof x-array
void quad_spline_matrix(double **mat, double *x, double *y, int n) {
  int ix = 0;
  for (int i = 0; i < 2 * (n - 1); i += 2) {
    int j = (i / 2) * 3;
    mat[i][j] = x[ix] * x[ix];
    mat[i][j + 1] = x[ix];
    mat[i][j + 2] = 1;
    mat[i][3 * (n - 1)] = y[ix];

    mat[i + 1][j] = x[ix + 1] * x[ix + 1];
    mat[i + 1][j + 1] = x[ix + 1];
    mat[i + 1][j + 2] = 1;
    mat[i + 1][3 * (n - 1)] = y[ix + 1];
    ix++;
  }

  for (int i = 2 * (n - 1), j = 0; j < (n - 2); i++, j++) {
    mat[i][3 * j] = 2 * x[j + 1];
    mat[i][3 * j + 1] = 1;

    mat[i][3 * j + 3] = -2 * x[j + 1];
    mat[i][3 * j + 4] = -1;
  }
  mat[3 * (n - 1) - 1][0] = 1;
}

void cubic_spline_matrix(double **mat, double *x, double *y, int n) {
  int ix = 0;
  n = n - 1;
  for (int i = 0; i < 2 * n; i += 2) {
    int j = (i / 2) * 4;
    mat[i][j] = x[ix] * x[ix] * x[ix];
    mat[i][j + 1] = x[ix] * x[ix];
    mat[i][j + 2] = x[ix];
    mat[i][j + 3] = 1;
    mat[i][4 * n] = y[ix];

    mat[i + 1][j] = x[ix + 1] * x[ix + 1] * x[ix + 1];
    mat[i + 1][j + 1] = x[ix + 1] * x[ix + 1];
    mat[i + 1][j + 2] = x[ix + 1];
    mat[i + 1][j + 3] = 1;
    mat[i + 1][4 * n] = y[ix + 1];
    ix++;
  }
  for (int i = 2 * n, j = 0; j < n - 1; i++, j++) {
    mat[i][4 * j] = 3 * x[j + 1] * x[j + 1];
    mat[i][4 * j + 1] = 2 * x[j + 1];
    mat[i][4 * j + 2] = 1;

    mat[i][4 * j + 4] = -3 * x[j + 1] * x[j + 1];
    mat[i][4 * j + 5] = -2 * x[j + 1];
    mat[i][4 * j + 6] = -1;
  }
  for (int i = 3 * n - 1, j = 0; j < n - 1; i++, j++) {
    mat[i][4 * j] = 6 * x[j + 1];
    mat[i][4 * j + 1] = 2;

    mat[i][4 * j + 4] = -6 * x[j + 1];
    mat[i][4 * j + 5] = -2;
  }
  // boundary conditions: natural spline
  mat[4 * n - 2][0] = 6 * x[0];
  mat[4 * n - 2][1] = 2;
  mat[4 * n - 1][4 * n - 3] = 6 * x[n];
  mat[4 * n - 1][4 * n - 2] = 2;
}

// n is the number of input given
void print_quad_spline_matrix(double **mat, int n) {
  int c = 0;
  char ch[] = {'a', 'b', 'c'};
  for (int i = 0; i < 3 * (n - 1); i++) {
    printf("%2d. ", i + 1);
    for (int j = 0; j < 3 * (n - 1); j++) {
      printf("%6.0lf", mat[i][j]);
    }
    printf("   %c%d ", ch[c], (i / 3) + 1);
    // if (i > 2 * (n - 1))
    //   printf("%5d", 0);
    // else
    printf("%6.0lf", mat[i][3 * (n - 1)]);
    c++;
    if (c == 3) c = 0;
    puts("");
  }
}

void print_cubic_spline_matrix(double **mat, int n) {
  int c = 0;
  char ch[] = {'a', 'b', 'c', 'd'};
  for (int i = 0; i < 4 * (n - 1); i++) {
    printf("%2d. ", i + 1);
    for (int j = 0; j < 4 * (n - 1); j++) {
      printf("%6d", (int)mat[i][j]);
    }
    printf("   %c%d ", ch[c], (i / 4) + 1);
    // if (i >= 2 * (n - 1))
    //   printf("%5d", 0);
    // else
    printf("%5d", (int)mat[i][4 * (n - 1)]);
    c++;
    if (c == 4) c = 0;
    puts("");
  }
}

// abc array contains value of abc. abc[i] contains <['a', 'b', 'c'][i%3]> <i/3>
// element ex: a1, b2, c3 arrx: x-array should be sorted n is the size of array
// arrx x is the input for f(x)
double quad_spline_f(double *abc, double *arrx, int n, double x) {
  // finding lower bound
  int l = 0, h = n - 1;
  while (l < h) {
    int m = (l + h) / 2;
    if (x < arrx[m]) {
      h = m - 1;
    } else {
      l = m;
    }
  }
  double a = abc[l * 3], b = abc[l * 3 + 1], c = abc[l * 3 + 2];
  return a * x * x + b * x + c;
}

// abc array contains value of abc. abc[i] contains <['a', 'b', 'c', 'd'][i%4]> <i/4>
// element ex: a1, b2, c3 arrx: x-array should be sorted n is the size of array
// arrx x is the input for f(x)
double cubic_spline_f(double *abc, double *arrx, int n, double x) {
  // finding lower bound
  int l = 0, h = n - 1;
  while (l < h) {
    int m = (l + h) / 2;
    if (x < arrx[m]) {
      h = m - 1;
    } else {
      l = m;
    }
  }
  double a = abc[l * 4], b = abc[l * 4 + 1], c = abc[l * 4 + 2],
         d = abc[l * 4 + 3];
  return a * x * x * x + b * x * x + c * x + d;
}