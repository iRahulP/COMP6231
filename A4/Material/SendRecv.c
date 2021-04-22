/* C Example */
#include <stdio.h>
#include <mpi.h>


int main (argc, argv)
     int argc;
     char *argv[];
{
  int rank, size;
  MPI_Status status;

  MPI_Init (&argc, &argv);	/* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);	/* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);	/* get number of processes */

  if (rank == 0){
  	int x = 10;
  	MPI_Send(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

  	x += 10;
  	MPI_Send(&x, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);

    x = 100;
    MPI_Send(&x, 1, MPI_INT, 1, 3, MPI_COMM_WORLD);

    x += 200;
    MPI_Send(&x, 1, MPI_INT, 1, 4, MPI_COMM_WORLD);

  }
  else
  {
  	int y; 
  	MPI_Recv(&y, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,&status); // status to check for success or errors.
  	printf("Recieved data from %d\n", y);
  	MPI_Recv(&y, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,&status);
  	printf("Recieved data from %d\n", y);

    MPI_Recv(&y, 1, MPI_INT, 0, 3, MPI_COMM_WORLD,&status); // status to check for success or errors.
    printf("Recieved data from %d\n", y);
    MPI_Recv(&y, 1, MPI_INT, 0, 4, MPI_COMM_WORLD,&status);
    printf("Recieved data from %d\n", y);

  }

  MPI_Finalize();
  return 0;
}