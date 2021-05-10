#include <stdio.h>
#include <omp.h>
#include "axpby.h"


void axpby(double* x, double* y, double a, double b, int n) {

    for (int i = 0; i < n; i++){
        y[i] = a*x[i] + b*y[i];
    }

}

void axpby_openmp(double* x, double* y, double a, double b, int n) {
    
    #pragma omp parallel for
    for (int i = 0; i < n; i++){
        y[i] = a*x[i] + b*y[i];
    }
    
}


void axpby_openmp_nofor(double* x, double* y, double a, double b, int n) {
    #pragma omp parallel
	{
	printf("Thread %d/%d [%d,%d]\n",omp_get_thread_num(),omp_get_num_threads(),omp_get_thread_num()*(n/omp_get_num_threads()),(omp_get_thread_num()+1)*(n/omp_get_num_threads()));
	for (int i = omp_get_thread_num()*(n/omp_get_num_threads()); i < (omp_get_thread_num()+1)*(n/omp_get_num_threads()); i++){
        y[i] = a*x[i] + b*y[i];
    }
	}
}


void print_stats(double start, double end, long int data_size) {
    double elapsed;
    double throughput = 0.0;
    elapsed = end - start;
    // TODO throughput
	throughput = ((double)(data_size/MEGA)/elapsed)/1000;
    printf("Data: %.0f MB\n", (double)(data_size/MEGA));
    printf("Time: %f sec\n", elapsed);
    printf("Throughput: %.2f GB/s\n", throughput);
}
