/* PI */ 

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>

/* Function f(x) */
double f(double a)
{
    return (4.0 / (1.0 + a*a));
}

double pi_cont_dist (long nrect, int rank, int nprocs)
{
   // TODO
    double prect = nrect / nprocs;

    double a= 0;
    double b= 1;
    double width = (b - a)/nrect;
    double x, local_sum = 0;
    for (int i = rank * prect; i < (rank + 1) * prect;i++){
        x = a + (i-1)*width;
        local_sum += width * f(x);
    }

    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
 
}

double pi_gaps_dist (long nrect, int rank, int nprocs)
{
   // TODO
   
    double a= 0;
    double b= 1;
    double width = (b - a)/nrect;
    double x, local_sum = 0;
    for (int i = rank; i < nrect;i+=rank){
        x = a + (i-1)*width;
        local_sum += width * f(x);   
    }

    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    return global_sum;
}

/* Main program */
int main (int argc, char *argv[])
{
  int    rank, nprocs;
  long   nrect;
  double pi, time, start, end;

  /* MPI Initialization */
  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD,&nprocs);
  MPI_Comm_rank (MPI_COMM_WORLD,&rank);

  /* Get parameters */
  if (argc == 2) {
      sscanf(argv[1],"%ld",&nrect);
      if (rank == 0) printf("rect. = %ld\n\n", nrect);
  }
  else
  {
      if (rank == 0) {
          printf("Usage: %s <number_of_rect>\n", argv[0]);
          MPI_Abort(MPI_COMM_WORLD,1);
      }
      exit(-1);
  }

  /* Compute pi using continuous distribution */
  start = MPI_Wtime();
  pi = pi_cont_dist (nrect, rank, nprocs);
  end = MPI_Wtime();

  if (rank == 0)
  {
     time = end - start;
     printf("Pi    = %.16f \n", pi);
     printf("Time continuous distr. = %.4f \n\n", time);
     fflush(stdout);
   }

  /* Compute pi using distribution with gaps */
  
  start = MPI_Wtime();
  pi = pi_gaps_dist (nrect, rank, nprocs);
  end = MPI_Wtime();
  if (rank == 0)
  {
     time = end - start;
     printf("Pi    = %.16f \n", pi);
     printf("Time distr. with gaps = %.4f \n", time);
     fflush(stdout);
   }

   /* End MPI */
   MPI_Finalize();
   return 0;
}

