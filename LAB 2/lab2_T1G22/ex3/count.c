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
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
	
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, FILENAME,MPI_MODE_RDONLY,MPI_INFO_NULL,&fh);
	
   /* Create datatype */
    MPI_Datatype recordtype;
	MPI_Datatype oldtypes[1];
	int blockcounts[1];
	MPI_Aint offsets[1];
	
	offsets[0] = 0;
	oldtypes[0] = MPI_INT;
	blockcounts[0] = 4;

	MPI_Type_create_struct (1, blockcounts, offsets, oldtypes, &recordtype);
	MPI_Type_commit (&recordtype);

	tRecord *buf;
	MPI_Status status;
	MPI_Offset filesize,bufsize;
	int recordtypesize, numrecords;
	
   /* Each process reads a part of the file */
   
	//no idea what to do here
	
   /* Each process determines number of records to read and initial offset */
	MPI_File_get_size (fh, &filesize);
	MPI_Type_size (recordtype, &recordtypesize);
	bufsize = filesize/nprocs;
    numrecords = bufsize/recordtypesize;

   /* Allocate buffer for records */
   buf =  (tRecord*) malloc(numrecords*sizeof(tRecord));
	
   /* Process reads numrecords consecutive elements */
	MPI_File_seek (fh, rank*bufsize, MPI_SEEK_SET);
	MPI_File_read (fh, buf, numrecords, recordtype, &status);

   /* Cound results by each process */
   total = 0;
   long localYes[MAX_QUEST],localNo[MAX_QUEST];
	for(int i = 0; i < MAX_QUEST; i++){
		localYes[i] = 0;
		localNo[i] = 0;
		totYes[i] = 0;
		totNo[i] = 0;
	}

	for(int i = 0; i < numrecords; i++){
		total = total + (buf[i].yes + buf[i].no);
		switch(buf[i].idQuestion){
			case 0: localYes[0] += buf[i].yes; localNo[0] += buf[i].no; break;
			case 1: localYes[1] += buf[i].yes; localNo[1] += buf[i].no; break;
			case 2: localYes[2] += buf[i].yes; localNo[2] += buf[i].no; break;
			case 3: localYes[3] += buf[i].yes; localNo[3] += buf[i].no; break;
			case 4: localYes[4] += buf[i].yes; localNo[4] += buf[i].no; break;
		}
	}

   /* Print local results */
   printf ("Proc %3d. Counted votes = %d\n", rank, total);
   fflush (stdout);
   
   MPI_Reduce(&localYes, &totYes, 5, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Reduce(&localNo, &totNo, 5, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD);

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
	MPI_Type_free (&recordtype);
   /* End MPI */
   MPI_File_close(&fh);
   MPI_Finalize();
   return 0;
}

