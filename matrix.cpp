#include "matrix.hpp"

#include <bits/stdc++.h>
using namespace std;

// absolute
// double abs(double n) { return n < 0 ? -n: n; }

// [][] array, column size, row1, row2
void swap_row(double **mat, int col, int r1, int r2) {
  for (int i = 0; i < col; i++) {
    double temp = mat[r1][i];
    mat[r1][i] = mat[r2][i];
    mat[r2][i] = temp;
  }
}

// send the array, row size, col size
void print_matrix(double **mat, int r, int c) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      printf("%g\t ", mat[i][j]);
    }
    puts("");
  }
}

// send the address of the array, row size, column size
// it will initialize the array with the specified size
void allocate_memory(double ***mat, int r, int c) {
  *mat = (double **)malloc(sizeof(double *) * r);
  // mat = new double*[r];

  // for each row allocate columns
  for (int i = 0; i < r; i++) {
    (*mat)[i] = (double *)malloc(sizeof(double) * c);
    // mat[i] = new double[c];
  }

  // initialize the array to 0
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      (*mat)[i][j] = 0;
    }
  }
}
void fill_matrix_with_random_number(double **mat, int r, int c) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      mat[i][j] = rand() % 100;
    }
  }
}

// performs partial pivoting |highest| element in pivot position
void partial_pivoting(double **mat, int r, int c) {
  int p = min(r, c);
  for (int i = 0; i < p; i++) {
    int i_max = i;
    for (int j = i + 1; j < r; j++) {
      if (abs(mat[i_max][i]) < abs(mat[j][i])) {
        i_max = j;
      }
    }
    if (i_max != i) {
      swap_row(mat, c, i_max, i);
    }
  }
}

// this is unsafe
void gaussian_elimination_without_partial_pivoting(double **mat, int r, int c) {
  for (int i = 0; i < r; i++) {
    for (int s = i + 1; s < r; s++) {
      if (mat[i][i] == 0) continue;
      double f = mat[s][i] / mat[i][i];
      mat[s][i] = 0;
      for (int t = i + 1; t < c; t++) {
        mat[s][t] = mat[s][t] - mat[i][t] * f;
      }
    }
  }
}

void gaussian_elimination(double **mat, int r, int c) {
  for (int i = 0; i < r; i++) {
    int i_max = i;
    for (int q = i + 1; q < r; q++) {
      if (abs(mat[i_max][i]) < abs(mat[q][i])) {
        i_max = q;
      }
    }
    if (mat[i_max][i] == 0) continue;
    if (i != i_max) {
      // swap (only right of i cols cz left of i are all 0)
      for (int u = i; u < c; u++) {
        double temp = mat[i_max][u];
        mat[i_max][u] = mat[i][u];
        mat[i][u] = temp;
      }
    }

    for (int s = i + 1; s < r; s++) {
      double f = mat[s][i] / mat[i][i];
      mat[s][i] = 0;
      for (int t = i + 1; t < c; t++) {
        mat[s][t] -= mat[i][t] * f;
      }
    }
  }
}

double *backward_substitute(double **mat, int n) {
  double *sol = (double *)malloc(sizeof(double) * n);
  memset(sol, 0, sizeof(double) * n);
  for (int x = n - 1; x >= 0; x--) {
    if (mat[x][x] == 0) {
      return sol;
    }

    sol[x] = mat[x][n];
    for (int i = x + 1; i < n; i++) {
      sol[x] -= mat[x][i] * sol[i];
    }
    sol[x] /= mat[x][x];
  }
  return sol;
}

// solves a given [n, n+1] matrix
// partially pivots, gaussian elimates
double *solve_offline_unsafe(double **mat, int n) {
  partial_pivoting(mat, n, n + 1);
#ifdef DEBUG
  cout << "After partial pivoting: " << endl;
  print_matrix(mat, n, n + 1);
#endif
  gaussian_elimination_without_partial_pivoting(mat, n, n + 1);
#ifdef DEBUG
  cout << "After gaussian elimiation: " << endl;
  print_matrix(mat, n, n + 1);
#endif
  return backward_substitute(mat, n);
}

// solves a given [n, n+1] matrix
// partially pivots, gaussian elimates
double *solve(double **mat, int n) {
  gaussian_elimination(mat, n, n + 1);
#ifdef DEBUG
  cout << "After gaussian elimiation: " << endl;
  print_matrix(mat, n, n + 1);
#endif
  return backward_substitute(mat, n);
}