#ifndef GAUSSIAN_PROCESS_H
#define GAUSSIAN_PROCESS_H


#define PI_GP 3.141592265358979323846
int matrix_index(int i, int j, int m);
double dexp(double *xp, double *xq, double l, int ndim);
double *gaussian_process(double *xs, int ns, double *x, double *y, int n, double l);

#endif //GAUSSIAN_PROCESS_H