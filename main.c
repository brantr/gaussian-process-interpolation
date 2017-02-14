#include <stdio.h>
#include <stdlib.h>
#include "gaussian_process.h"


int main(int arc, char **argv)
{
  //int matrix_layout = LAPACK_ROW_MAJOR;
  int n  = 5;
  int ns = 1000;
  
  double *x  = (double *) calloc(n,sizeof(double));
  double *xs = (double *) calloc(ns,sizeof(double));
  double *f  = (double *) calloc(n,sizeof(double));
  double *fs;

  //double l = 0.1;
  //double l = 0.5;
  double l = 1.0;

  int k;

  //set x and f, see figure 2.2 of Rasmussen & Williams
  //x[0] = -3.0*5.0/4.0;
  x[0] = -4.0;
  //x[1] = -2.0*5.0/4.0;
  x[1] = -3.0;
  //x[2] = -1.0*5.0/4.0;
  x[2] = -0.75;
  x[3] =  0.0;
  x[4] =  2.0;
  f[0] = -2.0;
  f[1] =  0.0;
  f[2] =  1.0;
  f[3] =  2.0;
  f[4] = -1.0;

  //make output locations
  for(k=0;k<ns;k++)
  {
    //make the sample
    xs[k] = 10.0*((double) k)/((double) (ns-1)) - 5.0;
  }

  //find mean gaussian proces interpolant
  fs = gaussian_process(xs,ns,x,f,n,l);

  for(k=0;k<ns;k++)
    printf("% e\t% e\n",xs[k],fs[k]);


  return 0;
}
