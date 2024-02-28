#include <stdio.h>
#include <mpi.h>
int main(int argc, char * argv[])
{
	int size, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;
	if (rank == 0)
	{
		int n;
		fprintf(stderr, "Enter a Number ");
		scanf("%d",&n);
		fprintf(stderr,"\nRank %d is Sending %d to Rank %d\n",rank,n,1);
		MPI_Send(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
		int x;
		MPI_Recv(&x,1,MPI_INT,size-1,1,MPI_COMM_WORLD,&status);
		fprintf(stderr,"\nFinally the Root process got back %d\n",x);

	}
	else if (rank == size-1)
	{
		int x;
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		fprintf(stderr,"\nThe Value in the Last process is %d\n",x);
		x = x+1;
		MPI_Send(&x,1,MPI_INT,0,1,MPI_COMM_WORLD);

	}
	else {
		int x;
		MPI_Recv(&x,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		x = x + 1;
		fprintf(stderr,"\nRank %d is Sending %d to Rank %d\n",rank,x,rank+1);

		MPI_Send(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}