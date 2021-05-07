#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () {

    #pragma omp parallel 
    {
        #pragma omp master
        {
            printf("Number of processors = %d\n", omp_get_num_procs());
            printf("Number of threads = %d\n", omp_get_num_threads());
            printf("Max threads = %d\n", omp_get_max_threads());
            printf("In parallel? = %d\n", omp_in_parallel());
            printf("Dynamic threads enabled? = %d\n", omp_get_dynamic());
            printf("Nested parallelism enabled? = %d\n", omp_get_nested());
        }
    }
    
    return 0;
}
