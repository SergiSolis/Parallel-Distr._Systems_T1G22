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
	int x = 1;
	int diagonal;
   //initialize a matrix with size*size dimensions 
   for (int i=0; i < size*size; i++){
		diagonal = size*x - x;
		if(i == diagonal && x <= size){
			matrix[i] = rank * x;
			x ++;
		}else{
			matrix[i] = 0;
		}
   }
}

void print_matrix (int *matrix, int size)
{
   //print the matrix 
    for (int i=0; i < size*size; i++){
	if(i % size == 0){
		printf("\n");
	}
      printf("%d\t", matrix[i]);
   }
}

int main (int argc, char* argv[]) 
{
   int *matrix, *result;
   int rank, size;
   int root;

   /* MPI Initialization */
    MPI_Init(&argc,&argv );
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
	root = size - 1;
   /* Matrix creation and initialization */
   
	matrix = new_matrix(size,rank);
	result = new_matrix(size,rank);
	init_matrix(matrix,size,rank);
	
   /* Print initial root matrix */
   if (rank == root) 
   {
      printf ("Initial Matrix (rank %d)\n", root);
      print_matrix (matrix, size);
   }
	printf("\n");
   /* Datatype vector creation */
   
	MPI_Datatype antidiagonaltype;
    MPI_Type_vector(size, 1, size-1, MPI_INT, &antidiagonaltype);
    MPI_Type_commit(&antidiagonaltype);
	
   /* Communication: root gathers all the diagonals from the other ranks */
   
	MPI_Gather(matrix,1,antidiagonaltype,result,size,MPI_INT,root,MPI_COMM_WORLD);
	
   /* Print final root matrix */
   if (rank == root) 
   {
      printf ("Final matrix (rank %d)\n", root);
      print_matrix (result, size);
   }
   /* Remember to free the datatype! */
   MPI_Type_free (&antidiagonaltype);
   MPI_Finalize();
   return 0;
}
