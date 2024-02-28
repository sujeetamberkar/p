#include <stdio.h>
#include <mpi.h>
int main (int argc, char * argv[])
{
	int size, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	if(rank%2==0)
		fprintf(stdout, "Rank is %d \t World\n",rank);
	else
		fprintf(stdout,"Rank is %d \t Hello \n",rank);


	MPI_Finalize();
	return 0;
}