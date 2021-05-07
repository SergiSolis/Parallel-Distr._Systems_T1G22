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
        
    #pragma omp parallel for reduction(+:total)
    for(i=0; i < N; i++) {
        total += arr[i];
    }
    
    printf("Sum of first %d numbers is %d\n", i, total);
    
    return 0;
}
