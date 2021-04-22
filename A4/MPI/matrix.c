#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define M 20                 
#define N 32                 
#define O 20               

#define MASTER 0               
#define FROM_MASTER 1          
#define FROM_WORKER 2          

int main (int argc, char *argv[]){

int numtasks,taskid,numworkers;
int source,dest;
int mtype,rows,averow;
int extra, offset; 

int i, j, k;
int rc;

double a[M][N],b[N][O],c[M][O];
		
MPI_Status status;
MPI_Init(&argc,&argv);

//Current process
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

//Total tasks
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

//set Workers
numworkers = numtasks-1;

//Start with first task
if (taskid == MASTER){
	double startTime = MPI_Wtime();
	printf("Matrix Multiplication has started with %d tasks.\n",numtasks);
	printf("Initializing arrays...\n");

	for (i=0; i<M; i++)
	 for (j=0; j<N; j++)
	    a[i][j] = i;

	for (i=0; i<N; i++)
	 for (j=0; j<O; j++)
	    b[i][j] = j;
	    
	printf("\n\tThe Initialized Arrays are:\n");
	
	printf("Array 1:\n");
	for (i=0; i<M; i++){
	 for (j=0; j<N; j++){
	    printf("%2.1f\t",a[i][j]);
	}printf("\n");
	}
	
	
	printf("Array 2:\n");
	for (i=0; i<N; i++){
	 for (j=0; j<O; j++){
	    printf("%2.1f\t",b[i][j]);
		}printf("\n");
	}

	averow = M/numworkers;
	extra = M%numworkers;
	offset = 0;
	//Sets Tag for Process
	mtype = FROM_MASTER;
      
	for (dest=1; dest<=numworkers; dest++){
	 rows = (dest <= extra) ? averow+1 : averow;   	
	 printf("Sending %d rows to task %d offset=%d\n",rows,dest,offset);
	 //send *buff,count, dType,dest,tag,comm
	 MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
	 MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
	 MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE, dest, mtype,MPI_COMM_WORLD);
	 MPI_Send(&b, N*O, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
	 offset = offset + rows;
	}

	//Sets Tag
	mtype = FROM_WORKER;
	for (i=1; i<=numworkers; i++){
	 source = i;
	 //recv *buff,count, dType,src,tag,comm,*status
	 MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
	 MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
	 MPI_Recv(&c[offset][0], rows*O, MPI_DOUBLE, source, mtype,MPI_COMM_WORLD, &status);
	 printf("Received results from task %d\n",source);
	}
	
	printf("\n\tThe Resultant 10*10 Multiplied Matrix is ::\n");
	for (i=0; i<M; i++){
	 printf("\n"); 
	 for (j=0; j<O; j++) 
	    printf("%4.1f   ", c[i][j]);
	}
	printf ("\n");

	double endTime = MPI_Wtime();

	printf("Total time elapsed :: %f\n", (endTime - startTime));
	}

	//Processing
	if (taskid > MASTER){
	mtype = FROM_MASTER;
	MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
	MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
	MPI_Recv(&a, rows*N, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
	MPI_Recv(&b, N*O, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

	for (k=0; k<O; k++)
	 for (i=0; i<rows; i++)
	 {
	    c[i][k] = 0.0;
	    for (j=0; j<N; j++)
	       c[i][k] = c[i][k] + a[i][j] * b[j][k];
	 }
	mtype = FROM_WORKER;
	MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
	MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
	MPI_Send(&c, rows*O, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
	}
   MPI_Finalize();
}
