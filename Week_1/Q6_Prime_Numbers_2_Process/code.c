#include<stdio.h>
#include<mpi.h>




int main (int argc, char * argv[])
{
	int rank, size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	 // Assuming we are using exactly 2 processes for this task
    if (rank == 0) {
       for(int i = 1; i<=50;i++)
       		{
       			fprintf(stderr, "i\t");
       		}
    } else if (rank == 1) {
        for(int i = 51; i<=100;i++)
       		{
       			fprintf(stderr, "i\t");
       		}
    }

	MPI_Finalize();
	return 0;
}