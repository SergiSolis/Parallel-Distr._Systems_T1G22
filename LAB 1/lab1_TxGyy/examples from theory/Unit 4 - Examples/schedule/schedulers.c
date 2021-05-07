#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <omp.h>

#define N 10

int main() {
    int i;
    double start, end;
    
    // static
    printf("static\n");
    start = omp_get_wtime();  
    #pragma omp parallel for schedule(static) num_threads(4)
    for (i=N;i>0;i--)     {
        printf("Thread %d sleeping %d sec\n", omp_get_thread_num(), i);
        sleep(i);  // wait for i seconds
    }
    end = omp_get_wtime();
    printf("static: %f seconds\n\n", end - start);

    // static 1
    printf("static 1\n");
    start = omp_get_wtime();  
    #pragma omp parallel for schedule(static, 1) num_threads(4)
    for (i=N;i>0;i--)     {
        printf("Thread %d sleeping %d sec\n", omp_get_thread_num(), i);
        sleep(i);  // wait for i seconds
    }
    end = omp_get_wtime();
    printf("static 1: %f seconds\n\n", end - start);
    
    // dynamic
    printf("dynamic\n");
    start = omp_get_wtime();  
    #pragma omp parallel for schedule(dynamic) num_threads(4)
    for (i=N;i>0;i--)     {
        printf("Thread %d sleeping %d sec\n", omp_get_thread_num(), i);
        sleep(i);  // wait for i seconds
    }
    end = omp_get_wtime();
    printf("dynamic: %f seconds\n\n", end - start);

    // dynamic 2
    printf("dynamic 2\n");
    start = omp_get_wtime();  
    #pragma omp parallel for schedule(dynamic, 2) num_threads(4)
    for (i=N;i>0;i--)     {
        printf("Thread %d sleeping %d sec\n", omp_get_thread_num(), i);
        sleep(i);  // wait for i seconds
    }
    end = omp_get_wtime();
    printf("dynamic 2: %f seconds\n\n", end - start);
    
    // guided
    printf("guided\n");
    start = omp_get_wtime();  
    #pragma omp parallel for schedule(guided) num_threads(4)
    for (i=N;i>0;i--)     {
        printf("Thread %d sleeping %d sec\n", omp_get_thread_num(), i);
        sleep(i);  // wait for i seconds
    }
    end = omp_get_wtime();   
    
    printf("guided: %f seconds\n\n", end - start);
    
    
    return 0;
}


