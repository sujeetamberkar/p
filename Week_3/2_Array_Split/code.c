#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

float average(int a[], int m)
{
	float sum = 0;
	for(int i = 0;i<m;i++)
	{
		sum = sum + a[i];
	}
	return (float) sum / m;
}
int main (int argc, char * argv[])
{
    int m;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Assuming m*size will not exceed 100, otherwise, dynamic allocation is needed.
    int A[100];
    int B[100]; // Each process will have its portion of A in B.
    float c;
    float C[100];
    if (rank == 0)
    {
        fprintf(stderr, "Enter m value: ");
        scanf("%d", &m);
        fprintf(stderr, "\nEnter %d Elements: ", m * size);
        for (int i = 0; i < m * size; ++i)
            scanf("%d", &A[i]);
    }

    // Broadcasting the value of m to all processes.
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the array A into parts of size m into array B of each process.
    MPI_Scatter(A, m, MPI_INT, B, m, MPI_INT, 0, MPI_COMM_WORLD);

    // Synchronize here to ensure Bcast and Scatter operations are completed.
    MPI_Barrier(MPI_COMM_WORLD);

    float ans = average(B,m);

    MPI_Gather(&ans,1,MPI_FLOAT,C,1,MPI_FLOAT,0,MPI_COMM_WORLD);

    if (rank==0)
    {
    	float sum = 0;
    	printf("\n");
    	for(int i =0;i <size;i++)
    		{
    			fprintf(stderr,"%f\t",C[i]);
    			sum = sum + C[i];
    		}

    	fprintf(stderr,"\n The Average is %f",sum/size);
    }

    // Printing the received portion in each process.

    // printf("Rank %d received: ", rank);
    // for (int j = 0; j < m; j++)
    // {
    //     printf("%d ", B[j]);
    // }
    // printf("\n");





    MPI_Finalize();
    return 0;
}
