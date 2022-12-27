#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <sys/time.h>
#define N 500
#define RANDLIMIT 5
#define NUMLIMIT 70.0

int main(void)
{
  float a[N][N], b[N][N], c[N][N];
  struct timeval start, stop;
  int i,j,k;

  for (i=0; i<N; i++){
    for (j=0; j<N; j++){
        a[i][i] = 1+(int)(NUMLIMIT*rand()/RAND_MAX+1.0);
        b[i][j] = (double)(rand()%RANDLIMIT);
    }
  }
 
  printf("\nMatrix A :\n");
  for (i=0; i<N; i++){
    for (j=0; j<N; j++)
        printf("%.3f\t",a[i][j]);
        printf("\n");
  }
 
  printf("\nMatrix B :\n");
  for (i=0; i<N; i++){
    for (j=0; j<N; j++)
        printf("%.3f\t",b[i][j]);
        printf("\n");
  }

  gettimeofday(&start, 0);
  for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        for (k = 0; k < N; k++) {
          c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
      }
  }
  gettimeofday(&stop, 0);

  printf("\nAnswer of Matrix Multiplication : \n "); 
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
        printf("%.2f \t", c[i][j] );
      printf(" \n ");
    }

  fprintf(stdout,"Time = %.6f\n\n",(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
  return 0;
}
