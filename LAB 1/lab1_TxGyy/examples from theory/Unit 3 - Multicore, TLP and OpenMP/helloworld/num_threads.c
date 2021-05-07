#include <omp.h>
#include <stdio.h>
#define N 1000

int main () {
    #pragma omp parallel
    {
        #pragma omp master
        printf("Total threads: %d\n", omp_get_num_threads());
    }
    
    omp_set_num_threads(2);
    #pragma omp parallel
    {
        #pragma omp master
        printf("Total threads: %d\n", omp_get_num_threads());
    }

    #pragma omp parallel num_threads(6)
    {
        #pragma omp master
        printf("Total threads: %d\n", omp_get_num_threads());
    }
    
    #pragma omp parallel if(N>=128) num_threads(3)
    {
        #pragma omp master
        printf("Total threads: %d\n", omp_get_num_threads());
    }
    
    return 0;
}
