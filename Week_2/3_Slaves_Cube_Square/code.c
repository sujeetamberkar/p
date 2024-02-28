#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
int main (int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	int bufsize = (size-1) * sizeof(int) + (size - 1)  * MPI_BSEND_OVERHEAD;
	void * buffer = malloc(bufsize);
	MPI_Buffer_attach(buffer,bufsize);
	if (rank == 0)
	{
		int array[size-1];
		fprintf(stderr, "Enter %d Numbers",size-1);
		for(int i = 0; i<size-1;i++)
			scanf("%d",&array[i]);

		for(int i = 1; i<size;i++)
			MPI_Bsend(&array[i-1],1,MPI_INT,i,i,MPI_COMM_WORLD);
	}

	else {
		int x;
		MPI_Recv(&x,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status);
		int temp = 0;
		if (rank % 2)
			temp = x * x;
		else
			temp = x * x * x;
		fprintf(stderr,"\n Rank = %d, x is %d, answer = %d ",rank,x,temp);
		MPI_Bsend(&temp,1,MPI_INT,0,0,MPI_COMM_WORLD);
	}

	if (rank == 0)
	{
		int array[size-1];
		for(int i = 1;i<size;i++)
		{
			MPI_Recv(&array[i-1],1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
		}
		fprintf(stderr,"\nThe Output is \n");
		for(int i = 0; i <size-1;i++)
			fprintf(stderr,"%d\t",array[i]);
	}
	MPI_Buffer_detach(&buffer, &bufsize);
	MPI_Finalize();
	return 0;
}