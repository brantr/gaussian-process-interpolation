
#include <mkl.h>
#include <math.h>
#include <stdlib.h>
#include "gaussian_process.h"


int matrix_index(int i, int j, int m)
{
  return (i-1)*m + j-1;
}
double dexp(double *xp, double *xq, double l, int ndim)
{
  //equation 2.16 of Rasmussen & Williams
  double k = 0;
  int i;
  for(i=0;i<ndim;i++)
    k+=(xp[i]-xq[i])*(xp[i]-xq[i]);
  return exp(-0.5*k/(l*l))/(sqrt(2*PI_GP)*l);
}
double *gaussian_process(double *xs, int ns, double *x, double *f, int n, double l)
{


  //int matrix_layout = LAPACK_ROW_MAJOR;
  char uplo = 'L';
  int  i,j,ij,ji;
  int  ndim = 1;
  int info;

  double *k_x_x = (double *) calloc(n*n, sizeof(double)); //correlation matrix
  double *fs    = (double *) calloc(ns,  sizeof(double)); //returned samples
  double *y     = (double *) calloc(n,   sizeof(double)); //projection

  double ks;

  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
      ij = matrix_index(i,j,n);
      k_x_x[ij] = dexp(&x[i-1],&x[j-1],l,ndim);
    }
  //get cholesky decomposition
  info = LAPACKE_dpotrf(LAPACK_ROW_MAJOR, uplo, n,  k_x_x,   n);
  //get inverse of lower triangle
  info = LAPACKE_dpotri(LAPACK_ROW_MAJOR, uplo, n,  k_x_x,   n);

  //get full inverse of k
  for(i=1;i<=n;i++)
    for(j=i;j<=n;j++)
    {
      ij = matrix_index(i,j,n);
      ji = matrix_index(j,i,n);
      k_x_x[ij] = k_x_x[ji];
    }

  // Take y = K^-1 f(x)
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
      ij = matrix_index(i,j,n);
      y[i-1] += k_x_x[ij]*f[j-1];
    }

  //take fs(xs) = ks^T y
  for(j=1;j<=ns;j++)
    for(i=1;i<=n;i++)
    {
      ks = dexp(&x[i-1],&xs[j-1],l,ndim);
      fs[j-1] += ks * y[i-1];
    }

  //free extra memory
  free(k_x_x);
  free(y);

  //return the answer
  return fs;

}
