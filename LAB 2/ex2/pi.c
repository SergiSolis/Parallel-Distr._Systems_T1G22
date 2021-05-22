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
   int a= 0; //limites
   int b=1;
   int width = (b - a)/nrect;
   int x, sum;
   for (int i= 0; i<nrect;i++){
       x = a + (i-1)*width;
       sum += width * f(x);
   }

   printf("");
}

double pi_gaps_dist (long nrect, int rank, int nprocs)
{
   // TODO
}

/* Main program */
int main (int argc, char *argv[])
{
  int    rank, nprocs;
  long   nrect;
  double pi, time;

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

  pi = pi_cont_dist (nrect, rank, nprocs);

  if (rank == 0)
  {
     time = //TODO
     printf("Pi    = %.16f \n", pi);
     printf("Time continuous distr. = %.4f \n\n", time);
     fflush(stdout);
   }

  /* Compute pi using distribution with gaps */

  pi = pi_gaps_dist (nrect, rank, nprocs);

  if (rank == 0)
  {
     time = // TODO
     printf("Pi    = %.16f \n", pi);
     printf("Time distr. with gaps = %.4f \n", time);
     fflush(stdout);
   }

   /* End MPI */
   MPI_Finalize();
   return 0;
}

