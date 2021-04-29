#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <omp.h>
#include "axpby.h"

int main(int argc, char* argv[]) {

    int i;
    int n;
    double *x;
    double *y;
    double a;
    double b;
    float *u;
    float *v;
    int memory;
    double start, end;
    struct timeval before, after;
        
    if(argc == 2) {
        n = atoi(argv[1]);
    } else {
        fprintf(stderr, "Wrong number of paramethers\nUsage:\n\t%s ARRAY_SIZE\n",argv[0]);
        return -1;
    }
    
    memory = (sizeof(float)*2*n + sizeof(double)*2*n) / MEGA;
    printf("Using %dMB of memory\n", memory);
    

    printf("\n\nInitialization\n");
    
    x = (double*)malloc(n * sizeof(double));
    y = (double*)malloc(n * sizeof(double));
    
    u = (float*)malloc(n * sizeof(float));
    v = (float*)malloc(n * sizeof(float));
    
    srand(time(NULL));
    a = (double)rand()/(double)(RAND_MAX/n);
    b = (double)rand()/(double)(RAND_MAX/n);
    
    for(i=0; i < n; i++) {
        x[i] = (double)rand()/(double)(RAND_MAX/n);
        y[i] = (double)rand()/(double)(RAND_MAX/n);
        
        u[i] = (float)x[i];
        v[i] = (float)y[i];
    }

    printf("\n\naxpby sequential\n");

    start = omp_get_wtime();
    axpby(x, y, a, b, n);
    end = omp_get_wtime();
    print_stats(start, end, sizeof(double)*2*n);


    printf("\n\naxpby OpenMP\n");

    start = omp_get_wtime();
    axpby_openmp(x, y, a, b, n);
    end = omp_get_wtime();
    print_stats(start, end, sizeof(double)*2*n);

    printf("\n\naxpby OpenMP no for\n");

    start = omp_get_wtime();
    axpby_openmp_nofor(x, y, a, b, n);
    end = omp_get_wtime();
    print_stats(start, end, sizeof(double)*2*n);
    return 0;
}