#include<stdio.h>

int main() {
    int x=1;
    #pragma omp parallel num_threads(2)
    {
        #pragma omp atomic
         x++;
    }
    printf("%d\n",x);
    return 0;
}
