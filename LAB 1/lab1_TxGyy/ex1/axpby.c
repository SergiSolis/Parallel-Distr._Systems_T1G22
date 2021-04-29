#include <stdio.h>
#include <omp.h>
#include "axpby.h"


void axpby(double* x, double* y, double a, double b, int n) {
    // TODO
    int n;
    size_t n_a = sizeof(x)/sizeof(x[0]);
    size_t n_b = sizeof(y)/sizeof(y[0]);
    if (n_a != n_b){
        break;
    }else{
        n = n_a;
    }
    pritnf("First vector\n")
    for (int i = 0; i < n; i++){
        pritnf("%lf"; x[i])
    }
    pritnf("\nSecond vector\n")
    for (int i = 0; i < n; i++){
        pritnf("%lf"; y[i])
    }
    for (int i = 0; i < n; i++){
        y[i] = a*x[i] + b*[i];
    }
    pritnf("\nResult\n")
    for (int i = 0; i < n; i++){
        pritnf("%lf"; y[i])
    }
}

void axpby_openmp(double* x, double* y, double a, double b, int n) {
    // TODO
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
