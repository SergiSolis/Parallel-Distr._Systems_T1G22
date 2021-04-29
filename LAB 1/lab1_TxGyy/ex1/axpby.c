#include <stdio.h>
#include <omp.h>
#include "axpby.h"


void axpby(double* x, double* y, double a, double b, int n) {
    // TODO
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
