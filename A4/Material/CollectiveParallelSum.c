#include <mpi.h>
#include <stdio.h>

#define NUM_OF_ELEM 1000
#define NUM_OF_PROCS 4
#define ELEM_PER_PROC (NUM_OF_ELEM/NUM_OF_PROCS)

#define ROOT 0

int main(int argc, char **argv) {
	
	int num_procs;
	int my_pid;
	
	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_pid);
	
	int sendBuffer[NUM_OF_ELEM];
	int recvBuffer[ELEM_PER_PROC];

	double start_time;

	# Root process initializes array  
	if (my_pid == ROOT) {
		
		start_time = MPI_Wtime();
		
		int i;
		for (i = 0; i < NUM_OF_ELEM; i++)
			sendBuffer[i] = i+1;
		
	}

	# Scatter the numbers  
	MPI_Scatter(sendBuffer, ELEM_PER_PROC, MPI_INT, recvBuffer, ELEM_PER_PROC, MPI_INT, ROOT, MPI_COMM_WORLD);
	
	int partial_sum = 0;
	
	# Calculate partial sum
	int j;
	for (j = 0; j < ELEM_PER_PROC; j++)
		partial_sum += recvBuffer[j];
	
	int total_sum;
	
	# Get total sum via reducing from all the processes
	MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT,  MPI_SUM, ROOT, MPI_COMM_WORLD);
	
	# Print time and sum from the root
	if (my_pid == ROOT) {
		double end_time = MPI_Wtime();
		printf("Total summation of 1 to %d is %d and it took %f\n", NUM_OF_ELEM, total_sum, end_time-start_time);

	}
	
	MPI_Finalize();

}
