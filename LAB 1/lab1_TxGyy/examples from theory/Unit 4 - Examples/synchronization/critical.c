
#include<stdio.h>

int main() {
    int x =1, y=0;
    #pragma omp parallel num_threads ( 4 )
    {
        #pragma omp critical(x)
        x++;
        #pragma omp critical(y)
        y++;
    }
    printf("x: %d\n",x);
    printf("y: %d\n",y);
    
    return 0;
}
