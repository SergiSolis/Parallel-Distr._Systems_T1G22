/* POLLING */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* Definitions */
#define MAX_QUEST 5
#define FILENAME "./votations.dat"

typedef struct {
     int idTable;
     int idQuestion;
     int yes;
     int no;
  }  tRecord;

/* Main program */
int main (int argc, char **argv)
{
   int   rank, nprocs;
   int   i;
   long  total, totYes[MAX_QUEST];
   long  totNo[MAX_QUEST];

   /* MPI Initialization */

   /* Create datatype */

   /* Each process reads a part of the file */

   /* Each process determines number of records to read and initial offset */

   /* Allocate buffer for records */

   /* Process reads numrecords consecutive elements */

   /* Cound results by each process */

   /* Print local results */
   printf ("Proc %3d. Counted votes = %d\n", rank, total);
   fflush (stdout);

   /* Print global results on process 0 */

   if (rank == 0)
   {
      total = 0;
      printf ("------------------------------------------------------------\n");
      for (i=0; i<MAX_QUEST; i++) 
      {
         total += totYes[i] + totNo[i];
	 printf("Question %d: yes: %.1f%% (%d) no: %.1f%% (%d)\n", i, totYes[i]*100.0/(totYes[i] + totNo[i]), totYes[i], totNo[i]*100.0/(totYes[i] + totNo[i]), totNo[i]);
         fflush (stdout);
      }

      printf ("------------------------------------------------------------\n");
      printf ("Total votes = %d\n", total);
      fflush (stdout);
   }

   /* Free datatype */

   /* End MPI */
   return 0;
}

