#include<stdio.h>
#define N 100

int main() {
    int x[N], y[N], z[N];
    int i;
    
    for(i=0; i < N; i++) {
        x[i] = i;
        y[i] = i;
    }
        
    #pragma omp parallel for simd
    for(i=0;i<N;i++) {
        z[i] = x[i] + y[i];
    }
    
    printf("z[%d]=%d\n",N/2,z[N/2]);
    
    return 0;
}
