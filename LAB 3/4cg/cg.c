#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<openacc.h>


#define N 1024
#define ROWSIZE 9



void spmv_gpu(int offset, int nsize, double* vals, int* cols, double* x, double* y)
{
}



void axpy_gpu(int offset, int nsize, double alpha, double* x, double* y)
{
}



double dot_product_gpu(int offset, int nsize, double* vector1, double* vector2)
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


void create_solution_and_rhs(int vecsize, double* Avals, int* Acols, double* xsol, double* rhs)
{

    for(int i=0; i< vecsize; i++)
        xsol[i] = sin(i*0.1) + cos(i*0.01);

    spmv_cpu(0, vecsize, Avals, Acols, xsol, rhs);


}

void cg_gpu(int offset, int length, double* Avals, int* Acols, double* rhs, double* x)
{

    int iterations= 500;

    double *Ax, *r0, *p0;
    double alpha, beta, rho1, rho0, denom;

    Ax = (double*) malloc (length*sizeof(double));
    r0 = (double*) malloc (length*sizeof(double));
    p0 = (double*) malloc (length*sizeof(double));



    for(int i=offset; i< length; i++)
    {
        r0[i] = rhs[i];
    }


    spmv_gpu(offset, length, Avals, Acols, x , Ax);
    

    axpy_gpu(offset, length, -1.0, Ax, r0);


    for(int i=offset; i< length; i++)
    {
        p0[i] = r0[i];
    }


    for( int k=0; k < iterations; k++) 
    {

        spmv_gpu(offset, length, Avals, Acols, p0 , Ax);
 
        rho0 = dot_product_gpu(offset, length, r0, r0);
        denom = dot_product_gpu(offset, length, p0, Ax);

        alpha = rho0/denom;

        axpy_gpu( offset, length, alpha, p0, x);

        axpy_gpu( offset, length, -1.0*alpha, Ax, r0);

        rho1 = dot_product_gpu (offset, length, r0 ,r0 );

        if(k % 20 == 0)
            printf("Iteration %d, residual %e\n",k, rho1);


        beta = rho1/rho0;

        for(int i=offset; i< length; i++)
            p0[i] = r0[i] + beta*p0[i];
    }

}

int main()
{


    double* x_gpu;
    double* x_sol;
    double* rhs;

    double* Avals;
    int*    Acols;

    int     vec_size = N*N;
    int     offset,length;
    double  time_start, time_end, time_cpu, time_gpu;

    double  norm2=0.0;


    x_gpu = (double*) malloc (vec_size*sizeof(double));
    x_sol = (double*) malloc (vec_size*sizeof(double));
    rhs =   (double*) malloc (vec_size*sizeof(double));

    Avals = (double*) malloc (ROWSIZE*vec_size*sizeof(double));
    Acols = (int*) malloc (ROWSIZE*vec_size*sizeof(int));

    for(int i = 0; i < vec_size; i++)
    {
        x_gpu[i] = 0.0;
        x_sol[i] = 0.0;
        rhs[i] = 0.0;
    }


    fill_matrix(Avals, Acols);
    create_solution_and_rhs(vec_size,Avals, Acols, x_sol, rhs);



    offset=0;
    length=vec_size-offset;

    acc_init( acc_device_nvidia );




    time_start = omp_get_wtime();


    cg_gpu(offset, length, Avals, Acols, rhs, x_gpu);

    time_end = omp_get_wtime();

    time_gpu = time_end - time_start;



    //Comparison between gpu and cpu results
    norm2=0.0;
    for(int i=offset; i<length; i++)
        norm2 += (x_gpu[i]-x_sol[i])*(x_gpu[i]-x_sol[i]);

    norm2= sqrt(norm2);

    printf("cg comparison cpu vs gpu error: %e, offset %d, size %d\n", norm2, offset, length);

    printf("Time: %lf\n", time_gpu);


}