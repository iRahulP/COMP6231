#include <stdio.h>
#include <mpi.h>


#define NUM_ELEMS 20
#define NUM_ELEM_PER_PROC 10
#define NUM_PROCS 2

#define TAG_X 1
#define TAG_Y 2

int sendBuff[NUM_ELEMS];
int recvBuff[NUM_ELEM_PER_PROC];


int main(int argc, char **argv){

	int myRank;    
	MPI_Status status;

	int sum = 0;


    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	if (myRank == 0)
	{
		//Master.
		
		double startTime = MPI_Wtime();

		int i;
		for(i = 0; i < NUM_ELEMS; i++)
			sendBuff[i] = i+1;

		
		int j;
		for(j=1; j<NUM_PROCS; j++)
		{
			int startIndex = j * NUM_ELEM_PER_PROC;
			int endIndex = startIndex + NUM_ELEM_PER_PROC;

			MPI_Send(&sendBuff[startIndex], NUM_ELEM_PER_PROC, MPI_INT, j, TAG_X, MPI_COMM_WORLD); 
		}

		int l;
		for(l=0; l < NUM_ELEM_PER_PROC; l++)
			sum += sendBuff[l];

		int partial_sum = 0;
		MPI_Recv(&partial_sum, 1, MPI_INT, 1, TAG_Y, MPI_COMM_WORLD, &status);

		sum += partial_sum;

		double endTime = MPI_Wtime();

		printf("Grand Sum = %d and it took = %f\n", sum, (endTime - startTime)); 

	
	}

	else
	{
	//Slave.
	
		MPI_Recv(&recvBuff, NUM_ELEM_PER_PROC, MPI_INT, 0, TAG_X, MPI_COMM_WORLD, &status);

		int partial_sum = 0;

		int k;
		for(k=0; k < NUM_ELEM_PER_PROC; k++)
			partial_sum += recvBuff[k];

		MPI_Send(&partial_sum, 1, MPI_INT, 0, TAG_Y, MPI_COMM_WORLD); 
	
	}
	
	MPI_Finalize();
}