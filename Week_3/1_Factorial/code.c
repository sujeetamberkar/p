#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int factorial(int a)
{
	int fact = 1;
	for(int i = 1; i <=a;i++)
		fact=fact*i;

	return fact;
}
int main (int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int A[100],B[100];
	int c;

	if (rank==0)
	{
		int n;
		fprintf(stderr, "Enter %d Elements\t",size);
		for(int i = 0;i<size;i++)
			scanf("%d",&A[i]);
	}
	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	c = factorial(c);
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0)
	{
		fprintf(stderr,"\n");
		for(int i = 0;i<size;i++)
			fprintf(stderr,"%d\t",B[i]);
	}
	MPI_Finalize();
	return 0;

}