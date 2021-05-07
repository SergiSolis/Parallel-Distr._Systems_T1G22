#include<stdio.h>
#define N 100
int main() {
    int arr[N];
    int i;
    int total;
    
    total = 0;
    
    for(i=0; i < N; i++) {
        arr[i] = i;
    }
        
    #pragma omp parallel for simd reduction(+:total)
    for(i=0; i < N; i++) {
        total += arr[i];
    }
    
    printf("Total: %d\n",total);
    
    return 0;
}
