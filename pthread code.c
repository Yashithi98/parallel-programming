#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <assert.h>
#include <pthread.h>
#include <stdint.h>

#define RANDLIMIT 5 
#define N 500 
#define THREADS 5 
#define NUMLIMIT 70.0

void *slave (void *myid);
float a[N][N], b[N][N], c[N][N];

void *slave( void *myid )
{
    int x, low, high;
    if (N >= THREADS) { 
        x = N/THREADS;
        low = (uintptr_t) myid * x;
        high = low + x;
    } else {
        x = 1;
        low = (uintptr_t) myid;
        if (low >= N) { 
            high = low;
        } else {
        high = low +1; 
        }
    }

    int i, j, k;

    for (i=low; i<high; i++) {
        for (j=0; j<N; j++) {
            c[i][j] = 0.0;

            for (k=0; k<N; k++){
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    struct timeval start, stop;
    int i,j;
    pthread_t tid[THREADS];
    
    for (i=0; i<N; i++)
        for (j=0; j<N; j++) {
            a[i][j] = 1+(int) (NUMLIMIT*rand()/(RAND_MAX+1.0));
            b[i][j] = (double) (rand() % RANDLIMIT);
        }
 
    printf("\nMatrix A:\n");
    for (i=0; i<N; i++){
        for (j=0; j<N; j++)
            printf("%.3f\t",a[i][j]);
        printf("\n");
    }
    printf("\nMatrix B:\n");
    for (i=0; i<N; i++){
        for (j=0; j<N; j++)
            printf("%.3f\t",b[i][j]);
    printf("\n");
    }
    
    
    gettimeofday(&start, 0);
    
    for ( i=0; i<THREADS ; i++)
        if (pthread_create( &tid[i], NULL, slave, (void *)(long) i) != 0)
            perror ("Pthread create fails");
    
    for ( i=0; i<THREADS ; i++)
        if (pthread_join( tid[i], NULL) != 0 )
            perror ("Pthread join fails");
    
    
    gettimeofday(&stop, 0);

    printf("\nAnswer of Matrix Multiplication :  = \n");
    for (i=0; i<N; i++){
        for (j=0; j<N; j++)
            printf("%.2f\t",c[i][j]);
    printf("\n");
    }

    fprintf(stdout,"Time = %.6f\n\n",(stop.tv_sec+stop.tv_usec*1e-6)-(start.tv_sec+start.tv_usec*1e-6));
    return(0);
}
