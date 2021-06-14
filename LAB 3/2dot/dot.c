#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<openacc.h>

#define N 1024

double dot_product_cpu(int offset, int n, double* vector1, double* vector2)
{

}


double dot_product_gpu(int offset, int n, double* vector1, double* vector2)
{

}



int main()
{


    double* vector1;
    double* vector2;
    int     vec_size = N*N;
    double  dot_cpu, dot_gpu;
    int     offset,length;
    double  time_start, time_end, time_cpu, time_gpu;

    vector1 = (double*) malloc (vec_size*sizeof(double));
    vector2 = (double*) malloc (vec_size*sizeof(double));



    //Filling the vector with a sinusoidal for validating the subroutine
    for(int i = 0; i < vec_size; i++)
    {
        vector1[i] = sin(i*0.01);
        vector2[i] = cos(i*0.01);
    }

    acc_init( acc_device_nvidia );


    offset = 0;
    length = vec_size - offset;

    time_start = omp_get_wtime();

    for( int i=0; i<100; i++)
        dot_cpu = dot_product_cpu(offset, length, vector1, vector2);

    time_end = omp_get_wtime();
    time_cpu = time_end - time_start;


    time_start = omp_get_wtime();

    for( int i=0; i<100; i++)
        dot_gpu = dot_product_gpu(offset, length, vector1, vector2);

    time_end = omp_get_wtime();
    time_gpu = time_end - time_start;



    printf("Dot product cpu %e : gpu %e, offset %d, size %d\n", dot_cpu, dot_gpu, offset, length);

    printf("CPU Time: %lf\n", time_cpu);
    printf("GPU Time: %lf\n", time_gpu);


}
