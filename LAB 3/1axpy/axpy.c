#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<openacc.h>

#define N 1024

void axpy_cpu(int offset, int n, double alpha, double* x, double* y)
{

    for (int i = offset; i < n; i++){
       y[i] =  alpha * x[i] + y[i];
    }

}

void axpy_gpu(int offset, int n, double alpha, double* x, double* y)
{
    
    #pragma acc parallel loop 
    for (int i = offset; i < n; i++){
       y[i] =  alpha * x[i] + y[i];
    }

}


int main()
{


    double* x;
    double* y_cpu;
    double* y_gpu;

    int     vec_size = N*N;
    int     offset,length;
    double  time_start, time_end, time_cpu, time_gpu;

    double  norm2=0.0;
    double  alpha= 0.5;


    x = (double*) malloc (vec_size*sizeof(double));
    y_cpu = (double*) malloc (vec_size*sizeof(double));
    y_gpu = (double*) malloc (vec_size*sizeof(double));




    //Filling the vector with a sinusoidal for validating the subroutine
    for(int i = 0; i < vec_size; i++)
    {
        x[i] = sin(i*0.01);
        y_cpu[i] = cos(i*0.01);
        y_gpu[i] = cos(i*0.01);
    }

    acc_init( acc_device_nvidia );


    offset = 0;
    length = vec_size - offset;

    time_start = omp_get_wtime();

    for( int i=0; i<100; i++)
        axpy_cpu(offset, length, alpha, x, y_cpu);

    time_end = omp_get_wtime();
    time_cpu = time_end - time_start;


   time_start = omp_get_wtime();

 
    for( int i=0; i<100; i++)
        axpy_gpu(offset, length, alpha, x, y_gpu);


    time_end = omp_get_wtime();
    time_gpu = time_end - time_start;



    //Comparison between gpu and cpu results
    norm2=0.0;
    for(int i=offset; i<length; i++)
        norm2 += (y_cpu[i]-y_gpu[i])*(y_cpu[i]-y_gpu[i]);

    norm2= sqrt(norm2);

    printf("axpy comparison cpu vs gpu error: %e, offset %d, size %d\n", norm2, offset, length);

    printf("CPU Time: %lf\n", time_cpu);
    printf("GPU Time: %lf\n", time_gpu);


}
