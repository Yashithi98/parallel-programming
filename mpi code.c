#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "mpi.h"
#define N 500
#define RANDLIMIT 5
#define NUMLIMIT 70.0

MPI_Status status;

float a[N][N], b[N][N], c[N][N];

main(int argc, char **argv)
{
  int size,rank,from,to;
  struct timeval start, stop;
  int i,j,k;

  if (rank == 0) {
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        a[i][i] = 1+(int)(NUMLIMIT*rand()/RAND_MAX+1.0);
        b[i][j] = (double)(rand()%RANDLIMIT);
      }
    }
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

    from = rank * N/size;
    to = (rank+1) * N/size;
  
  gettimeofday(&start, 0);
  MPI_Bcast (b, N*N, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (a, N*N/size, MPI_INT, a[from], N*N/size, MPI_INT, 0, MPI_COMM_WORLD);
  
  
    for (i=from; i<to; i++) 
        for (j=0; j<N; j++) {
            c[i][j]=0;
            for (k=0; k<N; k++)
                c[i][j] = c[i][j]+ (a[i][k]*b[k][j]);
        }

    MPI_Gather (c[from], N*N/size, MPI_INT, c, N*N/size, MPI_INT, 0, MPI_COMM_WORLD);
    gettimeofday(&stop, 0);

    if (rank==0) {
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
        printf("\nAnswer of Matrix Multiplication : \n "); 
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++)
                printf("%.3f \t", c[i][j] );
            printf(" \n ");
        }
    }
   fprintf(stdout,"Time = %.6f\n\n",(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
  MPI_Finalize();
  return 0;
}}
