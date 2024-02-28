#include <stdio.h>
#include <mpi.h>
int main (int argc, char * argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if (rank == 0)
	{
		int num;
		fprintf(stderr, "Enter a Number");
		scanf("%d",&num);

		for(int i = 1;i<size;i++)
		{
			MPI_Send(&num,1,MPI_INT,i,0,MPI_COMM_WORLD);
		}
	}

	else {
		int x;
		MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		fprintf(stderr,"\nProcess id %d has got %d\n",rank,x)x;
	}
	MPI_Finalize();
}