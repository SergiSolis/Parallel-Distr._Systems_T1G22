/* 
   Collect anti-diagonal from matrices
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* create a new diagonal matrix with size*size dimensions */ 
int *new_matrix (int size, int rank)
{
   int *matrix, i, j;

   matrix = (int *) malloc (size*size*sizeof(int));
   return matrix;
}

void init_matrix (int *matrix, int size, int rank)
{
   //initialize a matrix with size*size dimensions 
   for (int i=0; i < size; i++){
      for(int j=0; j < size; j++){
         matrix[i][j] = 0;
      }
   }
}

void print_matrix (int *matrix, int size)
{
   //print the matrix 
    for (int i=0; i < size; i++){
       printf(" (");
      for(int j=0; j < size; j++){
         printf("%d ", matrix[i][j]);
      }
      printf(")\n");
   }
}

int main (int argc, char* argv[]) 
{
   int *matrix, *result;
   int rank, size;
   int root;

   /* MPI Initialization */

   /* Matrix creation and initialization */

   /* Print initial root matrix */
   if (rank == root) 
   {
      printf ("Initial Matrix (rank %d)\n", root);
      print_matrix (matrix, size);
   }

   /* Datatype vector creation */

   /* Communication: root gathers all the diagonals from the other ranks */

   /* Print final root matrix */
   if (rank == root) 
   {
      printf ("Final matrix (rank %d)\n", root);
      print_matrix (result, size);
   }

   /* Remember to free the datatype! */

   return 0;
}
