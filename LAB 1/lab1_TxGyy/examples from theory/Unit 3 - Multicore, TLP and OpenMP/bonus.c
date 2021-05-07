#include <stdio.h>
#include <sys/time.h>
#include <omp.h>
#include <limits.h>

#define MEGA 1000000
#define N 100
#define M 10000

int main() {
    int i;
    int j;
    int k;
    struct timeval before, after;
    long unsigned int elapsed;
    double time_inner;
    double time_outter;
    int x[N][N] = {{0}};

    gettimeofday(&before, NULL);    
    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            #pragma omp parallel for
            for (k=0; k<N; k++) {
                x[j][k]++;
                x[j][k]--;
            }
        }
    }
    gettimeofday(&after, NULL);    
    elapsed = (after.tv_sec - before.tv_sec) * 1000000 + after.tv_usec - before.tv_usec;
    time_inner = (double)(elapsed)/MEGA;
    printf("Inner parallel region: %f seconds\n", time_inner);

   
    gettimeofday(&before, NULL);    
    #pragma omp parallel private(i,j)
    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            #pragma omp for
            for (k=0; k<N; k++) {
                x[j][k]++;
                x[j][k]--;
            }
        }
    }
    gettimeofday(&after, NULL);    
    elapsed = (after.tv_sec - before.tv_sec) * 1000000 + after.tv_usec - before.tv_usec;
    time_outter = (double)(elapsed)/MEGA;
    printf("Outter parallel region: %f seconds\n", time_outter);

    printf("Second version is %0.2f times faster\n", time_inner/time_outter);

    return 0;
}


