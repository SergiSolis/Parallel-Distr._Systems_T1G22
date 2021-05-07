#include <omp.h>
#include <stdio.h>

int main () {
    int x =1;
    #pragma omp parallel firstprivate(x) num_threads(2)
    {
        x++;
        printf( "%d\n" , x );
    }
    printf( "%d\n" , x );
    
    return 0;
}
