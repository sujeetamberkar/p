#include <stdio.h>
#include <mpi.h>
#include <math.h>
int main (int argc, char *argv[])
{
	int rank, size;
	int x = 2;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int answer = pow(x,rank);

	fprintf(stdout,"The rank is %d and the pow(2,%d)=%d\n",rank,rank,answer);
	MPI_Finalize();
}