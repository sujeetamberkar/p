#include <stdio.h>
#include <mpi.h>
int main (int argc, char *argv[])
{
	int rank, size,c;
	int A[10], B[10];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);


	if (rank==0)
	{
		fprintf(stderr, "Enter %d Values:\t",size);
		for(int i = 0; i <size;i++)
			scanf("%d",&A[i]);
	}
	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	fprintf(stderr,"\nRank %d has %d\n",rank,c);
	c = c * c ;
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if (rank==0)
		for(int i = 0;i<size;i++)
			fprintf(stderr,"%d\t",B[i]);
	MPI_Finalize();
	return 0;
}