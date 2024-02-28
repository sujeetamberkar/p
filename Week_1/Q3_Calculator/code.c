#include <stdio.h>
#include <mpi.h>
int main(int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int answer;

	int a = 10;
	int b = 5;

	if(rank==0)
		answer = a+b;
	else if (rank==1)
		answer = a-b;
	else if (rank == 2)
		answer = a* b;
	else if (rank == 3)
		answer = a/b;
	else 
		answer = a %b;

	fprintf(stderr, "Rank %d and Output =%d\n",rank,answer);
	MPI_Finalize();

}