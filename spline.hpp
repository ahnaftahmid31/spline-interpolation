void quad_spline_matrix(double **mat, double *x, double *y, int n);
void cubic_spline_matrix(double **mat, double *x, double *y, int n);
void print_quad_spline_matrix(double **mat, int n);
void print_cubic_spline_matrix(double **mat, int n);
double quad_spline_f(double *abc, double *arrx, int n, double x);
double cubic_spline_f(double *abc, double *arrx, int n, double x);