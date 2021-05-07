#include <stdio.h>
#include <omp.h>
#include "axpby.h"


void axpby(double* x, double* y, double a, double b, int n) {

    printf("First vector\n");
    for(int i = 0; i < n; i++){
        printf("%lf ", a*x[i]);
    }
    printf("\nSecond vector\n");
    for (int i = 0; i < n; i++){
        printf("%lf ", b*y[i]);
    }
    for (int i = 0; i < n; i++){
        y[i] = a*x[i] + b*y[i];
    }
    printf("\nResult\n");
    for (int i = 0; i < n; i++){
        printf("%lf ", y[i]);
    }
}

void axpby_openmp(double* x, double* y, double a, double b, int n) {
    
    printf("First vector\n");
    #pragma omp parallel for
    for(int i = 0; i < n; i++){
        printf("%lf ", x[i]);
    }

    printf("\nSecond vector\n");
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        printf("%lf ", y[i]);
    }
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        y[i] = a*x[i] + b*y[i];
    }

    printf("\nResult\n");
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        printf("%lf ", y[i]);
    }
}


void axpby_openmp_nofor(double* x, double* y, double a, double b, int n) {
    // TODO
}


void print_stats(double start, double end, long int data_size) {
    double elapsed;
    double throughput = 0.0;
    elapsed = end - start;
    // TODO throughput
    printf("Data: %.0f MB\n", (double)(data_size/MEGA));
    printf("Time: %f sec\n", elapsed);
    printf("Throughput: %.2f GB/s\n", throughput);
}
