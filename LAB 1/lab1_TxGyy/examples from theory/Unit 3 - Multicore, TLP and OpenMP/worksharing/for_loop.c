#include <stdio.h>
#include <omp.h>

#define N 100000

int main() {
    int i;
    int x[N];
    int y[N];
    int z[N];

    for(i=0; i < N; i++) {
        x[i] = i;
        y[i] = i;
    }

    #pragma omp parallel for
    for(i=0;i<N;i++) {
        z[i] = x[i] + y[i];
    }

    printf("z[%d]=%d\n",N/2 ,z[N/2]);


    #pragma omp parallel
    {
        #pragma omp for
        for(i=0;i<N;i++) {
            z[i] -= x[i];
        }
    }

    printf("z[%d]=%d\n",N/2 ,z[N/2]);
    return 0;
}
