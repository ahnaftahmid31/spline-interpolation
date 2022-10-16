// [][] array, column size, row1, row2
void swap_row(double **mat, int col, int r1, int r2);

// matrix array, row size, col size
void print_matrix(double **mat, int r, int c);

// send the address of the array, row size, column size
// it will initialize the array with the specified size
void allocate_memory(double ***mat, int r, int c);

// fill a 2d array with random numbers less than 100
void fill_matrix_with_random_number(double **mat, int r, int c);

// performs partial pivoting on matrix
void partial_pivoting(double **mat, int r, int c);

// performs gaussian elimiation without partial pivoting
void gaussian_elimination_without_partial_pivoting(double **mat, int r, int c);

// performs gaussian elimination using partial pivoting online
void gaussian_elimination(double **mat, int r, int c);

// performs backward susbtitution on a reduced row form of a matrix
// returns the solution array
double *backward_substitute(double **mat, int n);

// solves a given [n, n+1] matrix
// partially pivots, gaussian elimates
double *solve_offline_unsafe(double **mat, int n);

double *solve(double **mat, int n);