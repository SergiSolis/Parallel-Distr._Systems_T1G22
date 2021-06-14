#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<openacc.h>

#define N 1024
#define ROWSIZE 9

void spmv_cpu(int offset, int nsize, double* vals, int* cols, double* x, double* y)
{
}



void spmv_gpu(int offset, int nsize, double* vals, int* cols, double* x, double* y)
{
}


void fill_matrix(double* vals, int* cols)
{

    int indx[ROWSIZE];
    int row_count=0;
    for(int j=0; j< N ; j++){
        for(int i=0; i<N; i++){

            indx[0] = i     + (j - 2)*N;
            indx[1] = i     + (j - 1)*N;
            indx[2] = i - 2 +       j*N;
            indx[3] = i - 1 +       j*N;
            indx[4] = i + j*N;
            indx[5] = i + 1 +       j*N;
            indx[6] = i + 2 +       j*N;
            indx[7] = i    +  (j + 1)*N;
            indx[8] = i    +  (j + 2)*N;


            for(int row=0; row < ROWSIZE; row++)
            {
                if(indx[row] < 0 || indx[row] >= N*N)
                {
                    cols[row + row_count*ROWSIZE] = i + j*N;
                    vals[row + row_count*ROWSIZE] = 0.0;
                }
                else
                {
                    cols[row + row_count*ROWSIZE] = indx[row];
                    if(row == 4)
                    {
                        vals[row + row_count*ROWSIZE] = 0.95;
                    }
                    else
                    {
                        vals[row + row_count*ROWSIZE] = -0.95/(ROWSIZE - 1);
                    }
                }
            }
            row_count++;
        }
    }

    vals[4 + (N*N/2 + N/2)*ROWSIZE] =  1.001*vals[4 + (N*N/2 + N/2)*ROWSIZE];
}


int main()
{


    double* x;
    double* y_cpu;
    double* y_gpu;

    double* Avals;
    int*    Acols;

    int     vec_size = N*N;
    int     offset,length;
    double  time_start, time_end, time_cpu, time_gpu;

    double  norm2=0.0;


    x = (double*) malloc (vec_size*sizeof(double));
    y_cpu = (double*) malloc (vec_size*sizeof(double));
    y_gpu = (double*) malloc (vec_size*sizeof(double));

    Avals = (double*) malloc (ROWSIZE*vec_size*sizeof(double));
    Acols = (int*) malloc (ROWSIZE*vec_size*sizeof(int));



    //Filling the vector with a sinusoidal for validating the subroutine
    for(int i = 0; i < vec_size; i++)
    {
        x[i] = sin(i*0.01);
        y_cpu[i] = 0.0;
        y_gpu[i] = 0.0;
    }


    fill_matrix(Avals, Acols);


    offset=0;
    length= vec_size-offset;

    acc_init( acc_device_nvidia );



    time_start = omp_get_wtime();

    for( int i=0; i<100; i++)
        spmv_cpu(offset, length, Avals, Acols, x, y_cpu);

    time_end = omp_get_wtime();
    time_cpu = time_end - time_start;




    time_start = omp_get_wtime();

    for( int i=0; i<100; i++)
        spmv_gpu(offset, length, Avals, Acols, x, y_gpu);

    time_end = omp_get_wtime();

    time_gpu = time_end - time_start;



    //Comparison between gpu and cpu results
    norm2=0.0;
    for(int i=offset; i<length; i++)
        norm2 += (y_cpu[i]-y_gpu[i])*(y_cpu[i]-y_gpu[i]);

    norm2= sqrt(norm2);

    printf("spmv comparison cpu vs gpu error: %e, offset %d, size %d\n", norm2, offset, length);

    printf("CPU Time: %lf\n", time_cpu);
    printf("GPU Time: %lf\n", time_gpu);


}
