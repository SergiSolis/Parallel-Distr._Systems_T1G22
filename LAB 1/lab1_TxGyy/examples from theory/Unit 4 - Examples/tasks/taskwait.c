#include<stdio.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("1\n");
            #pragma omp task
            {
                printf("2\n");
            }
            #pragma omp task
            {
                printf("3\n");
            }
            #pragma omp taskwait
            printf("4\n");
        }
    }
    return 0;
}

